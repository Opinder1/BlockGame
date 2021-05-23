#include "server.h"

Server::Server() : 
    log("server"s),
    config("server"s),
    server(this, config.get_value<uint16>("port"s, 1234), (uint8)config.get_value<uint16>("max_connections"s, 32))
{
    if (!log.initialized()) {
        return;
    }

    if (!config.initialized()) {
        log.println("Config could not be loaded\n");
        return;
    }

    config.save();

    if (!server.initialised()) {
        log.println("An error occurred while initializing server");
        return;
    }

    ocode::create_folder_if_not_exist("scenes"s);

    ocode::create_folder_if_not_exist("players"s);
}

Server::~Server() {

}

bool Server::on_tick(const TickEvent* e) {
    server.listen();
}

bool Server::on_player_join(const PlayerJoinEvent* e) {
    log.println("Player joined"s);
    /*
    Session session = reader.read<Session>();
    std::wstring username = reader.read_string<wchar>();

    bool auth = Client::is_valid_session(session, username);

    ocode::PacketWriter packet(ocode::UNENCRYPTED, PLAYER_JOIN);

    packet.write(auth);

    send_packet(e.get_peer(), packet.to_message());

    if (!auth) {
        return;
    }

    std::shared_ptr<Client> client(new Client(*this, peer, session, username));

    this->players.insert({ peer, client });
    */

    return false;
}

bool Server::on_player_leave(const PlayerLeaveEvent* e) {
    log.println("Player left"s);

    //this->players.erase(e->get_peer());

    return false;
}

bool Server::on_packet_recive(const PacketReciveEvent* e) {
    PacketReader reader = e->get_packet();

    return false;
}