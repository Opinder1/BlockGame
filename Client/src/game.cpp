#include "game.h"

float map(float n, float a1, float b1, float a2, float b2) {
    return ((n - a1) / (b1 - a1)) * (b2 - a2) + a2;
}

Game::Game() : client(engine::event_manager, "localhost", 1234), scene(engine::event_manager), camera(70.0f), material("polygon3d"), poly(&material) {

    int count = 0;

    for (int i = 0; i < count; i++) {
        glm::mat4 model = glm::mat4(1.0f);

        float p1 = map(float(r.new_int32()), float(INT32_MIN), float(INT32_MAX), float(-sqrt(count)), float(sqrt(count)));
        float p2 = map(float(r.new_int32()), float(INT32_MIN), float(INT32_MAX), float(-sqrt(count)), float(sqrt(count)));

        model = glm::translate(model, glm::vec3(p1, 0, p2));
        model = glm::scale(model, glm::vec3(1.0f));
        model = glm::rotate(model, float(r.new_int32() % 360), glm::vec3(r.new_int32() / 1000.0f, r.new_int32() / 1000.0f, r.new_int32() / 1000.0f));

        poly.new_instance(model);
    }

    application->window.set_mouse_type(GLFW_CURSOR_DISABLED);
    //application->window.set_fullscreen(true);

    engine::event_manager->EVENT_SUBSCRIBE(engine::KeyActionEvent, Game::on_key_action);
}

Game::~Game() {

}

void Game::on_connect() {

}

void Game::on_disconnect() {

}

int tick = 0;
void Game::update() {
    int speed = 1;
    if (application->window.get_key(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed *= 5;
    }

    if (application->window.get_key(GLFW_KEY_W) == GLFW_PRESS) {
        move_camera(glm::vec3(speed, 0, 0));
    }

    if (application->window.get_key(GLFW_KEY_S) == GLFW_PRESS) {
        move_camera(glm::vec3(-speed, 0, 0));
    }

    if (application->window.get_key(GLFW_KEY_A) == GLFW_PRESS) {
        move_camera(glm::vec3(0, 0, -speed));
    }

    if (application->window.get_key(GLFW_KEY_D) == GLFW_PRESS) {
        move_camera(glm::vec3(0, 0, speed));
    }

    if (application->window.get_key(GLFW_KEY_SPACE) == GLFW_PRESS) {
        move_camera(glm::vec3(0, speed, 0));
    }

    if (application->window.get_key(GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        move_camera(glm::vec3(0, -speed, 0));
    }

    if (application->window.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        application->running = false;
    }

    camera.update(application->window.get_mouse_pos());

    material.use();

    material.set_mat4("camera", camera.get_projection());

    poly.draw();

    {
        glm::mat4 model = glm::mat4(1.0f);

        float time = glfwGetTime() * 10.0f;

        model = glm::translate(model, glm::vec3(cos(time) * time, 0, sin(time) * time));
        model = glm::scale(model, glm::vec3(1.0f));
        model = glm::rotate(model, float(r.new_int32() % 360), glm::vec3(r.new_int32() / 1000.0f, r.new_int32() / 1000.0f, r.new_int32() / 1000.0f));

        poly.new_instance(model);

        if (tick % 2 == 1) {
            poly.delete_instance(poly.instance_count() / 2);
        }
        tick++;
    }
}

void Game::move_camera(glm::vec3 translation) {
    translation = glm::rotate(translation, -camera.rotation.x, camera.up_direction());
    translation = glm::rotate(translation, -camera.rotation.y, camera.left_direction());
    camera.position += translation;
}

bool mouse_toggle;
bool Game::on_key_action(const engine::KeyActionEvent* e) {
    //application->log.println("key action: %i %i %i %i\n", e->key, e->scancode, e->action, e->mods);

    if (e->key == GLFW_KEY_C && e->action == GLFW_PRESS) {
        if (mouse_toggle) {
            application->window.set_mouse_type(GLFW_CURSOR_DISABLED);
            mouse_toggle = false;
        }
        else {
            application->window.set_mouse_type(GLFW_CURSOR_NORMAL);
            mouse_toggle = true;
        }
    }

    return false;
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