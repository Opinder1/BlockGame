#include "game.h"

Game::Game() : client(engine::event_manager, "localhost", 1234), scene(engine::event_manager), camera(70.0f) {

}

Game::~Game() {

}

/*
void Game::on_connect() {
    bool connected = false;

    for (uint8 i = 0; i < options.connect_attempts; i++) {
        log.println("Attempting to connect");
        connected = ocode::Client::connect(options.connect_timeout);

        if (connected) {
            break;
        }
    }

    if (!connected) {
        log.println("Could not connect to server");
    }

    ocode::PacketWriter writer(ocode::UNENCRYPTED, MessageTypes::PLAYER_JOIN);

    ocode::Random r;

    Session s = { 0, 0, 0, 0, uuid(r) };

    writer.write(s);
    writer.write<std::string>("data");

    send_packet(writer.to_message());

    log.println("Joined server");

    return connected;
}
*/

void Game::update() {

}