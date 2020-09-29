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

        PacketReader packet(event.packet);

        uint8 net_packet_type = packet.read<uint8>();

        switch (net_packet_type) {
        case PacketReader::DEFAULT:
            do {
                uint8 packet_type = packet.read<uint8>();

                uint32 packet_size = packet.read<uint32>();

                uint8* packet_data = packet.segment(packet_size);

                packet_recive(packet_type, { packet_data, packet_size });
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

void NetClient::packet_send(PacketWriter& packet) {
    ENetPacket* enet_packet = packet.to_packet();

    enet_peer_send(server, 0, enet_packet);

    enet_packet_destroy(enet_packet);

    enet_host_flush(client);
}