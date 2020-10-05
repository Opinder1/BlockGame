#include "server.h"

Server::Server(uint16 port, uint8 max_connections) : network::Server(port, max_connections), log("server") {
    if (!initialised()) {
        log.println("An error occurred while initializing server");

        WorkerThread::stop_running();
    }

    ocode::create_folder_if_not_exist("scenes");

    ocode::create_folder_if_not_exist("players");
}

Server::~Server() {

}

bool Server::initialised() {
	return network::Server::initialised() and log.initialised();
}

bool Server::is_running() {
    return running;
}

void Server::on_tick() {
    network::Server::poll_netevent();
}

void Server::packet_recive(network::Peer peer, uint8 type, network::PacketReader& packet) {
    switch (type) {
    case PacketType::PEER_CONNECT:
        log.println("Peer connect\n");
        return;

    case PacketType::PEER_DISCONNECT:
        log.println("Peer disconnect\n");
        return;

    case PacketType::PLAYER_JOIN:
        player_join(peer, packet);
        return;

    case PacketType::PLAYER_LEAVE:
        player_leave(peer, packet);
        return;

    default:
        //dostuff
        return;
    }
}

void Server::player_join(network::Peer peer, network::PacketReader& reader) {
    Session session = reader.read<Session>();
    std::string username = reader.read<std::string>();

    std::shared_ptr<Player> client(new Player(this, peer, session, username));

    this->players.insert({ peer, client });

    log.println("Player joined");
}

void Server::player_leave(network::Peer peer, network::PacketReader& reader) {
    this->players.erase(peer);

    log.println("Player left");
}