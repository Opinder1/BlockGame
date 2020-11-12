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

    bool on_packet_send(const PacketSendEvent* e);
};

class NetServer : public Host {
private:
    ENetAddress address;

public:
    NetServer(ocode::EventManager* manager, uint16 port, uint8 max_connections);
    virtual ~NetServer();

    bool on_packet_send(const PacketSendEvent* e);
    bool on_packet_broadcast(const PacketBroadcastEvent* e);
};

class PeerConnectEvent : ocode::Event {
private:
    ENetPeer* peer;

public:
    PeerConnectEvent(ENetPeer* peer) : peer(peer) {}

    inline const std::string to_string() const override {
        return std::string("PeerConnect: ");
    }

    const ENetPeer* get_peer() const;
};

class PeerDisconnectEvent : ocode::Event {
private:
    ENetPeer* peer;
    uint32 reason;

public:
    PeerDisconnectEvent(ENetPeer* peer, uint32 reason) : peer(peer), reason(reason) {}

    inline const std::string to_string() const override {
        return std::string("PeerDisconnect: ") + std::to_string(reason);
    }

    const ENetPeer* get_peer() const;
    const uint32 get_reason() const;

};