#include "client.h"

Client::Client(std::string ip, uint16 port) : network::Client(ip, port), log("client") {
    if (!initialised()) {
        log.println("An error occurred while initializing client");

        WorkerThread::stop_running();
    }
}

Client::~Client() {
    
}

bool Client::initialised() {
	return network::Client::initialised() and log.initialised();
}

bool Client::is_running() {
	return running;
}

void Client::on_tick() {
    network::Client::poll_netevent();
}

void Client::packet_recive(network::Peer peer, uint8 type, network::PacketReader& packet) {
    switch (type) {
    case PacketType::PEER_CONNECT:
        log.println("Peer connect\n");
        return;

    case PacketType::PEER_DISCONNECT:
        log.println("Peer disconnect\n");
        return;

    default:
        //dostuff
        return;
    }
}

void Client::connect(uint8 connect_attempts, uint16 connect_timeout) {
    for (uint8 i = 0; i < connect_attempts; i++) {
        log.println("Attempting to connect");
        network::Client::attempt_connect(connect_timeout);

        if (network::Client::is_connected()) {
            break;
        }
    }

    if (!network::Client::is_connected()) {
        log.println("Could not connect to server");

        WorkerThread::stop_running();
    }

    network::PacketWriter packet(PacketType::PLAYER_JOIN);

    ocode::Random r;

    Session s = { 0, 0, 0, 0, uuid::generate(r) };

    packet.write(s);
    packet.write(std::string("da"));

    network::Client::send_packet(packet);

    log.println("Joined server");
}