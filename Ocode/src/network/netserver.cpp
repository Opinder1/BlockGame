#include "nethost.h"

namespace ocode {
    std::string peer_to_string(ENetPeer* peer) {
        char buffer[64];

        sprintf_s(buffer, 64, "%u.%u.%u.%u:%u", (peer->address.host & 255) ^ 255, (peer->address.host >> 8 & 255) ^ 255, (peer->address.host >> 16 & 255) ^ 255, (peer->address.host >> 24 & 255) ^ 255, peer->address.port);

        return buffer;
    }

    Server::Server(uint16 port, uint8 max_connections) {
        address = { ENET_HOST_ANY, (uint16)port };

        host = enet_host_create(&address, max_connections, 2, 0, 0);
    }

    Server::~Server() {
        enet_host_destroy(host);
    }

    void Server::send(Peer client, PacketWriter& packet) {
        PacketGroup packets;

        packets.write_packet(packet);

        ENetPacket* enet_packet = packets.to_packet();

        enet_peer_send((ENetPeer*)client, 0, enet_packet);

        enet_packet_destroy(enet_packet);

        enet_host_flush(host);
    }

    void Server::send_multiple(ENetPeer* client, PacketGroup& packets) {
        ENetPacket* enet_packet = packets.to_packet();

        enet_peer_send((ENetPeer*)client, 0, enet_packet);

        enet_packet_destroy(enet_packet);

        enet_host_flush(host);
    }

    void Server::broadcast(PacketWriter& packet) {
        PacketGroup packets;
        packets.write_packet(packet);

        ENetPacket* enet_packet = packets.to_packet();

        enet_host_broadcast(host, 0, enet_packet);

        enet_packet_destroy(enet_packet);

        enet_host_flush(host);
    }
}