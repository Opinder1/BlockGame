#include "player.h"

Player::Player(network::Server* host, network::Peer peer, Session session, std::string username) : host(host), peer(peer), session(session), username(username) {

    printf("player::username: %s\n", username.c_str());

    std::stringstream stream;

    stream << "players/";
    stream << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << session.unique_id.first;
    stream << "-";
    stream << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << session.unique_id.last;
    stream << ".player";
    data_file_name = stream.str();

    printf("player::data_file_name: %s\n", data_file_name.c_str());

    load_data_file(data_file_name, data);
}

Player::~Player() {
    //Player not deleted on leave
    //Error with stream for some reason
    save_data_file(data_file_name, data);
}

const Session& Player::get_session() {
    return session;
}

const std::string& Player::get_username() {
    return username;
}

void Player::send_packet(network::PacketWriter& packet) {
    host->send_packet(peer, packet);
}