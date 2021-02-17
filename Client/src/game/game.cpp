#include "game.h"

Game::Game() : camera(90.0f, application->window.get_size()), surface(application->window.get_size(), 4), scene(engine::event_manager) {
    tilemap::init();

    camera.position = { 0, 30, 0 };

    camera_buffer.set_data<glm::mat4>(1, nullptr, engine::BufferType::Static);

    tilemap::set_screen_size(application->window.get_size());

    engine::event_manager->EVENT_SUBSCRIBE(engine::KeyActionEvent, Game::on_key_action);
    engine::event_manager->EVENT_SUBSCRIBE(engine::WindowResizeEvent, Game::on_window_resize);
}

Game::~Game() {
    tilemap::deinit();
}

void Game::controls() {
    float speed = 0.2;
    if (application->window.get_key(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed *= 20;
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
}

void Game::set_camera() {
    camera.update(application->window.get_mouse_pos());

    tilemap::set_camera_rot(camera.rotation);
    tilemap::set_camera_pos(camera.position);

    glm::mat4 p = camera.get_projection();
    camera_buffer.modify_data(0, 1, &p);
    camera_buffer.activate_slot(0);
}

void Game::render() {
    engine::set_multisample(true);
    engine::set_alphatest(true);
    engine::set_depthtest(true);
    //engine::set_culling(engine::Culling::Back);

    surface.clear();

    tilemap::draw(glm::vec3(0, 0, 0), glm::vec3(10000, 256, 10000));

    application->surface.draw(surface.texture);
}

void Game::update() {
    controls();

    set_camera();

    render();
}

void Game::move_camera(glm::vec3 translation) {
    translation = glm::rotate(translation, -camera.rotation.x, camera.up_direction());
    translation = glm::rotate(translation, -camera.rotation.y, camera.left_direction());
    camera.position += translation;
}

void Game::on_key_action(const engine::KeyActionEvent* e) {
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
}

void Game::on_window_resize(const engine::WindowResizeEvent* e) {
    surface.resize(e->size, 4);
    tilemap::set_screen_size(e->size);
}