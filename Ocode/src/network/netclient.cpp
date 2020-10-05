#include "nethost.h"

namespace ocode {
    Client::Client(std::string ip, uint16 port) : server(NULL) {
        enet_address_set_host(&server_address, ip.c_str());
        server_address.port = port;

        host = enet_host_create(NULL, 1, 2, 0, 0);
    }

    Client::~Client() {
        if (server != NULL) {
            enet_peer_disconnect(server, 0);
        }
        enet_host_destroy(host);
    }

    bool Client::is_connected() {
        return connected;
    }

    void Client::connect(uint16 timeout) {
        ENetEvent event;

        server = enet_host_connect(host, &server_address, 2, 0);

        if (enet_host_service(host, &event, timeout) > 0 and event.type == ENET_EVENT_TYPE_CONNECT) {
            connected = true;
        }
        else {
            enet_peer_reset(server);
            connected = false;
        }
    }

    void Client::send(PacketWriter& packet) {
        PacketGroup packets;
        packets.write_packet(packet);

        ENetPacket* enet_packet = packets.to_packet();

        enet_peer_send(server, 0, enet_packet);

        enet_packet_destroy(enet_packet);

        enet_host_flush(host);
    }

    void Client::send_multiple(PacketGroup& packets) {
        ENetPacket* enet_packet = packets.to_packet();

        enet_peer_send(server, 0, enet_packet);

        enet_packet_destroy(enet_packet);

        enet_host_flush(host);
    }
}