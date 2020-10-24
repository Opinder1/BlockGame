#include "client.h"

bool Client::is_valid_session(Session session, const std::wstring& username) {
    return true;
}

Client::Client(Server& server, ENetPeer* peer, Session session, const std::wstring& username) : server(server), peer(peer), session(session), username(username) {

    data_file_name = "players/" + session.unique_id.to_string() + ".player";

    load_data_file(data_file_name, data); 

    printf("username: %s\n", username.c_str());

    printf("data_file_name: %s\n", data_file_name.c_str());
}

Client::~Client() {
    //Player not deleted on leave
    //Error with stream for some reason
    save_data_file(data_file_name, data);
}

const Session& Client::get_session() {
    return session;
}

const std::wstring& Client::get_username() {
    return username;
}

void Client::send_packet(Packet* packet) {
    //server.post_thread_event(e);
}