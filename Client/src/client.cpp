#include "client.h"

Client::Client() :
    running(true),
    log("client.log"),
    config("client.yml"),
    window(this, "test")
{
    if (!log.initialized()) {
        return;
    }

    if (!config.initialized()) {
        log.println("Config could not be loaded\n");
        return;
    }

    config.save();

    if (!window.initialized()) {
        log.println("Window failure\n");
        return;
    }

    Monitor::init(this);

    EVENT_SUBSCRIBE(PacketReciveEvent, on_packet_recive);
    EVENT_SUBSCRIBE(WindowResizeEvent, on_window_resize);

    do {
        tick();
    } while (running);
}

Client::~Client() {

}

void Client::tick() {
    glfwPollEvents();

    layers.tick(window);

    window.update();
}

int Client::connect() {
    /*
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
    */
    return 0;
}

bool Client::on_packet_recive(const PacketReciveEvent* e) {
    return false;
}

bool Client::on_window_resize(const WindowResizeEvent* e) {
    glViewport(0, 0, e->get_width(), e->get_height());
    return false;
}