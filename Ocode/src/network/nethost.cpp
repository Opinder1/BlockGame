#include "nethost.h"

namespace ocode {
    bool Host::initialised() {
        return host != NULL;
    }

    void Host::listen() {
        if (!initialised()) {
            return;
        }

        ENetEvent event;

        enet_host_service(host, &event, 1000);

        switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
        {
            PacketReader packet = { (uint8*)&event.data, 4 };
            recive((Peer)event.peer, 0, packet);
            break;
        }

        case ENET_EVENT_TYPE_DISCONNECT:
        {
            PacketReader packet = { (uint8*)&event.data, 4 };
            recive((Peer)event.peer, 1, packet);
            break;
        }

        case ENET_EVENT_TYPE_RECEIVE:
        {
            PacketReader packet = PacketReader(event.packet);

            packet_recive((Peer)event.peer, packet);

            break;
        }
        }

        enet_packet_destroy(event.packet);
    }

    void Host::packet_recive(Peer peer, PacketReader& packet) {
        uint8 net_packet_type = packet.read<uint8>();

        printf("whole_size: %u\n", packet.size());

        switch ((NetPacketType)net_packet_type) {
        case NetPacketType::DEFAULT:
            do {
                uint8 packet_type = packet.read<uint8>();
                printf("packet_type: %u\n", packet_type);

                uint32 packet_size = packet.read<uint32>();
                printf("packet_size: %u\n", packet_size);

                PacketReader packet_segment = packet.segment(packet_size);

                recive(peer, packet_type, packet_segment);
            } while (!packet.reached_end());

            break;

        case NetPacketType::SSL_FROM:
            break;

        case NetPacketType::SSL_TO:
            break;
        }
    }
}