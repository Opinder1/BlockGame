#include "network.h"

std::string peer_to_string(ENetPeer* peer) {
    char buffer[64];

    sprintf_s(buffer, 64, "%u.%u.%u.%u:%u", (peer->address.host & 255) ^ 255, (peer->address.host >> 8 & 255) ^ 255, (peer->address.host >> 16 & 255) ^ 255, (peer->address.host >> 24 & 255) ^ 255, peer->address.port);

    return buffer;
}

bool Host::initialised() {
    return host != NULL;
}

void Host::listen() {
    ENetEvent event;

    while (enet_host_service(host, &event, 0) > 0) {
        switch (event.type) {
        case ENET_EVENT_TYPE_CONNECT:
            manager->event_post(PeerConnectEvent, event.peer);
            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            manager->event_post(PeerDisconnectEvent, event.peer, (uint32)event.data);
            break;

        case ENET_EVENT_TYPE_RECEIVE:
            switch ((PacketType)event.packet->data[0]) {
            case PacketType::UNENCRYPTED:
                manager->event_post(PacketReciveEvent, event.peer, (PacketType)event.packet->data[1], (uint8*)event.packet->data + 2, (uint32)event.packet->dataLength - 1);
                break;

            case PacketType::SSL_FROM:
                break;

            case PacketType::SSL_TO:
                break;

            default:
                break;
            }

            enet_packet_destroy(event.packet);
            break;

        default:
            break;
        }

    }
}

NetClient::NetClient(ocode::EventManager* manager, const std::string& address, uint16 port) : Host(manager), server(NULL) {
    enet_address_set_host(&server_address, address.c_str());
    server_address.port = port;

    host = enet_host_create(NULL, 1, 2, 0, 0);

    manager->event_subscribe(PacketSendEvent, on_packet_send);
}

NetClient::~NetClient() {
    if (server != NULL) {
        enet_peer_disconnect(server, 0);
    }
    enet_host_destroy(host);
}

bool NetClient::connect(uint16 timeout) {
    ENetEvent event;

    server = enet_host_connect(host, &server_address, 2, 0);

    if (enet_host_service(host, &event, timeout) > 0 and event.type == ENET_EVENT_TYPE_CONNECT) {
        return true;
    }
    else {
        enet_peer_reset(server);
        return false;
    }
}

NetServer::NetServer(ocode::EventManager* manager, uint16 port, uint8 max_connections) : Host(manager) {
    address = { ENET_HOST_ANY, (uint16)port };

    host = enet_host_create(&address, max_connections, 2, 0, 0);

    manager->event_subscribe(PacketSendEvent, on_packet_send);
    manager->event_subscribe(PacketBroadcastEvent, on_packet_broadcast);
}

NetServer::~NetServer() {
    enet_host_destroy(host);
}

void NetServer::on_packet_send(const PacketSendEvent* e) {
    enet_peer_send(e->peer, 0, e->packet);
}


void NetServer::on_packet_broadcast(const PacketBroadcastEvent* e) {
    enet_host_broadcast(host, 0, e->packet);
}

void NetClient::on_packet_send(const PacketSendEvent* e) {
    enet_peer_send(server, 0, e->packet);
}