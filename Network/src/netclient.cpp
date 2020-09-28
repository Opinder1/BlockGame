#include "netclient.h"

NetClient::NetClient(std::string ip, uint16 port) : server(NULL) {
    enet_address_set_host(&server_address, ip.c_str());
    server_address.port = port;

    client = enet_host_create(NULL, 1, 2, 0, 0);
}

NetClient::~NetClient() {
    enet_host_destroy(client);
}

bool NetClient::initialised() {
    return client != NULL;
}

bool NetClient::is_connected() {
    return connected;
}

void NetClient::attempt_connect(uint16 timeout) {
    ENetEvent event;

    server = enet_host_connect(client, &server_address, 2, 0);

    if (enet_host_service(client, &event, timeout) > 0 and event.type == ENET_EVENT_TYPE_CONNECT) {
        connected = true;
    } else {
        enet_peer_reset(server);
        connected = false;
    }
}

void NetClient::poll_netevent() {
    ENetEvent event;

    enet_host_service(client, &event, 1000);

    switch (event.type) {
    case ENET_EVENT_TYPE_DISCONNECT:
        disconnect();
        break;

    case ENET_EVENT_TYPE_RECEIVE:
        packet_recive({ 0, event.packet->data, event.packet->dataLength });

        size_t pos = 0;

        while (pos < event.packet->dataLength) {
            uint8 packet_type = *(uint8*)(event.packet->data + pos);
            pos += sizeof(uint8);

            uint64 packet_size = *(uint64*)(event.packet->data + pos);
            pos += sizeof(uint64);

            char* packet_data = (char*)(event.packet->data + pos);

            switch (packet_type) {

            }

            packet_recive({ packet_type, packet_data, packet_size });
        }

        enet_packet_destroy(event.packet);
        break;
    }
}

void NetClient::packet_send(Packet packet) {
    ENetPacket* enet_packet = packet.to_enet_packet();

    enet_peer_send(server, 0, enet_packet);

    enet_packet_destroy(enet_packet);

    enet_host_flush(client);
}