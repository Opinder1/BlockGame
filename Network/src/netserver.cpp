#include "netserver.h"

std::string peer_to_string(ENetPeer* client) {
    char buffer[64];

    sprintf_s(buffer, 64, "%u.%u.%u.%u:%u", (client->address.host & 255) ^ 255, (client->address.host >> 8 & 255) ^ 255, (client->address.host >> 16 & 255) ^ 255, (client->address.host >> 24 & 255) ^ 255, client->address.port);

    return buffer;
}

NetServer::NetServer(uint16 port, uint8 max_connections) {
    address = { ENET_HOST_ANY, (uint16)port };

    server = enet_host_create(&address, max_connections, 2, 0, 0);
}

NetServer::~NetServer() {
    enet_host_destroy(server);
}

bool NetServer::initialised() {
    return server != NULL;
}

void NetServer::poll_netevent() {
    ENetEvent event;

    enet_host_service(server, &event, 100);

    switch (event.type) {
    case ENET_EVENT_TYPE_CONNECT:
        connect((Peer)event.peer);

        break;

    case ENET_EVENT_TYPE_DISCONNECT:
        disconnect((Peer)event.peer);

        break;

    case ENET_EVENT_TYPE_RECEIVE:
        //ocode::println("A packet of length %llu containing %s was received from %s on channel %u.", event.packet->dataLength, (char*)event.packet->data, peer_to_string(peer), event.channel);

        packet_recive((Peer)event.peer, { 0, event.packet->data, event.packet->dataLength });

        size_t pos = 0;

        while (pos < event.packet->dataLength) {
            uint8 packet_type = *(uint8*)(event.packet->data + pos);
            pos += sizeof(uint8);

            uint64 packet_size = *(uint64*)(event.packet->data + pos);
            pos += sizeof(uint64);

            char* packet_data = (char*)(event.packet->data + pos);

            switch (packet_type) {

            }

            packet_recive((Peer)event.peer, { packet_type, packet_data, packet_size });
        }

        enet_packet_destroy(event.packet);

        break;
    }
}

void NetServer::packet_send(Peer client, Packet packet) {
    ENetPacket* enet_packet = packet.to_enet_packet();

    enet_peer_send((ENetPeer*)client, 0, enet_packet);

    enet_packet_destroy(enet_packet);

    enet_host_flush(server);
}

void NetServer::packet_broadcast(Packet packet) {
    ENetPacket* enet_packet = packet.to_enet_packet();

    enet_host_broadcast(server, 0, enet_packet);

    enet_packet_destroy(enet_packet);

    enet_host_flush(server);
}