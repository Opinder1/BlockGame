#include "server.h"

Server::Server(uint16 port, uint8 max_connections) : NetServer(port, max_connections), log("server"), commands(this) {
    if (!initialised()) {
        log.println("An error occurred while initializing server");

        WorkerThread::stop_running();
    }

    ocode::create_folder_if_not_exist("scenes");

    ocode::create_folder_if_not_exist("players");

    new_scene(0);
}

Server::~Server() {

}

bool Server::initialised() {
	return NetServer::initialised() and log.initialised();
}

bool Server::is_running() {
    return running;
}

void Server::on_tick() {
    //log.println("Server tick");
    NetServer::poll_netevent();
}

void Server::connect(Peer client) {
	log.println("%u Connected", client);
}

void Server::disconnect(Peer client) {
	log.println("%u Disconnected", client);
}

void Server::packet_recive(Peer peer, uint8 type, PacketReader packet) {
    switch (type) {
    case 0:
        log.println("%u Packet: %s", peer, packet.read_string(packet.size()).c_str());
        break;

    case 1:
        player_join(peer, packet);
        break;

    case 2:
        player_leave(peer, packet);
        break;

    case 3:
        //Update

    case 4:
        //

    default:
        //dostuff
        break;
    }
}

void Server::player_join(Peer peer, PacketReader& reader) {
    ocode::UUID id = reader.read<ocode::UUID>();

    ocode::Config player_config(id.to_string() + ".yml");

    uint8 username_size = reader.read<uint8>();
    std::string username = reader.read_string(username_size);

    std::shared_ptr<Client> client(new Client(username, peer));

    this->players.insert({ peer, client });
}

void Server::player_leave(Peer peer, PacketReader& reader) {
    this->players.erase(peer);
}

void Server::new_scene(uint32 id) {
    this->scenes.emplace(id, new Scene());
}