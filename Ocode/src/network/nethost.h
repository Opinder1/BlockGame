#pragma once

#include "typedef.h"

#include <atomic>

#include <enet/enet.h>
#include <cryptlib/cryptlib.h>
#include <cryptlib/sha.h>

#include "packet.h"

namespace ocode {

    typedef uint64 Peer;

    std::string peer_to_string(ENetPeer* peer);

    class Host {
    private:
        void packet_recive(Peer peer, PacketReader& packet);

    protected:
        ENetHost* host;

    public:
        bool initialised();

        void listen();

        virtual void recive(Peer peer, uint8 type, PacketReader& packet) = 0;
    };

    class Client : public Host {
    private:
        ENetAddress server_address;
        ENetPeer* server;
        std::atomic_bool connected;

    public:
        Client(std::string ip, uint16 port);
        virtual ~Client();

        bool is_connected();

        void connect(uint16 timeout);

        void send(PacketWriter& packet);
        void send_multiple(PacketGroup& packets);
    };

    class Server : public Host {
    private:
        ENetAddress address;

    public:
        Server(uint16 port, uint8 max_connections);
        virtual ~Server();

        void send(Peer client, PacketWriter& packet);
        void send_multiple(ENetPeer* client, PacketGroup& packets);
        void broadcast(PacketWriter& packet);
    };
}