#pragma once

#include "typedef.h"

#include <atomic>

#include "enet/enet.h"
#include "packet.h"

class NetClient {
private:
    ENetHost* client;

    ENetAddress server_address;
    ENetPeer* server;
    std::atomic_bool connected;

public:
    NetClient(std::string ip, uint16 port);
    virtual ~NetClient();

    bool initialised();
    bool is_connected();

    void attempt_connect(uint16 timeout);
    void poll_netevent();

    virtual void disconnect() = 0;
    virtual void packet_recive(uint8 type, PacketReader packet) = 0;

    void packet_send(PacketWriter& packet);
    //void packet_send_multiple(Packet* packets);
};