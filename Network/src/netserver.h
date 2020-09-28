#pragma once

#include "typedef.h"

#include "enet/enet.h"
#include "packet.h"

std::string peer_to_string(ENetPeer* client);

typedef uint64 Peer;

class NetServer {
private:
    ENetHost* server;

    ENetAddress address;

public:
    NetServer(uint16 port, uint8 max_connections);
    virtual ~NetServer();

    bool initialised();

    void poll_netevent();

    virtual void connect(Peer client) = 0;
    virtual void disconnect(Peer client) = 0;
    virtual void packet_recive(Peer client, Packet packet) = 0;

    void packet_send(Peer client, Packet packet);
    //void packet_send_multiple(ENetPeer* client, Packet* packets);
    void packet_broadcast(Packet packet);
};