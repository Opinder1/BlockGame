#pragma once

#include "ocode.h"

#include <enet/enet.h>
#include <cryptlib/cryptlib.h>
#include <cryptlib/sha.h>

#include "packet.h"

class ENetInit {
public:
    inline ENetInit() {
        if (enet_initialize() == 0) {
            initialised = true;
        }
    }

    inline ~ENetInit() {
        enet_deinitialize();
    }

    inline static bool initialised = false;
};

inline ENetInit ENetInit_instance;

std::string peer_to_string(ENetPeer* peer);

class Host : public ocode::EventDevice {
protected:
    ENetHost* host;

public:
    Host(const Host&) = delete;
    Host(ocode::EventManager* m) : host(NULL), EventDevice(m) {}

    bool initialised();

    void listen();
};

class NetClient : public Host {
private:
    ENetAddress server_address;
    ENetPeer* server;

public:
    NetClient(ocode::EventManager* manager, const std::string& address, uint16 port);
    virtual ~NetClient();

    bool connect(uint16 timeout);

    void on_packet_send(const PacketSendEvent* e);
};

class NetServer : public Host {
private:
    ENetAddress address;

public:
    NetServer(ocode::EventManager* manager, uint16 port, uint8 max_connections);
    virtual ~NetServer();

    void on_packet_send(const PacketSendEvent* e);
    void on_packet_broadcast(const PacketBroadcastEvent* e);
};

struct PeerConnectEvent : ocode::Event {
    ENetPeer* peer;

    PeerConnectEvent(ENetPeer* peer) : peer(peer) {}
};

struct PeerDisconnectEvent : ocode::Event {
    ENetPeer* peer;
    uint32 reason;

    PeerDisconnectEvent(ENetPeer* peer, uint32 reason) : peer(peer), reason(reason) {}
};