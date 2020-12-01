#include "client.h"

Client::Client() :
    running(true),
    log("client"),
    config("client"),
    window(get_manager(), "test")
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

    engine::Monitor::init(get_manager());

    EVENT_SUBSCRIBE(engine::WindowResizeEvent, Client::on_window_resize);
    EVENT_SUBSCRIBE(engine::WindowCloseEvent, Client::on_window_close);
}

Client::~Client() {

}

void Client::run() {
    while (running) {
        update();
    }
}

void Client::update() {
    glfwPollEvents();

    window.use();
    glClear(GL_COLOR_BUFFER_BIT);

    layers.update();

    window.update();
}

ocode::EventManager* Client::get_manager() {
    return this;
    //return reinterpret_cast<ocode::EventManager*>(this);
}

bool Client::on_window_resize(const engine::WindowResizeEvent* e) {
    glViewport(0, 0, e->get_width(), e->get_height());
    return false;
}

bool Client::on_window_close(const engine::WindowCloseEvent* e) {
    running = false;

    return false;
}

Client* client;

void client_init() {
    if (client == NULL) {
        client = new Client();
    }
}

void client_run(Layer* initial_layer) {
    if (client != NULL) {
        client->layers.insert(initial_layer);

        client->run();

        delete client;
    }
}