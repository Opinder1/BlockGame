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
        PacketReader packet(event.packet);

        uint8 net_packet_type = packet.read<uint8>();

        switch (net_packet_type) {
        case PacketReader::DEFAULT:
            do {
                uint8 packet_type = packet.read<uint8>();

                uint32 packet_size = packet.read<uint32>();

                uint8* packet_data = packet.segment(packet_size);

                packet_recive((Peer)event.peer, packet_type, { packet_data, packet_size });
            } while (!packet.reached_end());

            break;

        case PacketReader::SSL_FROM:
            break;

        case PacketReader::SSL_TO:
            break;
        }

        enet_packet_destroy(event.packet);
        break;
    }
}

void NetServer::packet_send(Peer client, PacketWriter& packet) {
    ENetPacket* enet_packet = packet.to_packet();

    enet_peer_send((ENetPeer*)client, 0, enet_packet);

    enet_packet_destroy(enet_packet);

    enet_host_flush(server);
}

void NetServer::packet_broadcast(PacketWriter& packet) {
    ENetPacket* enet_packet = packet.to_packet();

    enet_host_broadcast(server, 0, enet_packet);

    enet_packet_destroy(enet_packet);

    enet_host_flush(server);
}