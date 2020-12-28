 #include "mainmenu.h"

MainMenu::MainMenu() : camera(45.0f, 1.0f, 1.0f, 0.1f, 1000000.0f), material("polygon3d"), poly(&material) {
    application->window.set_mouse_type(GLFW_CURSOR_DISABLED);

    ocode::Random r;

    for (unsigned int i = 0; i < 1000000; i++) {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(r.new_int32() / 1000000.0, r.new_int32() / 100000000.0, r.new_int32() / 1000000.0));
        model = glm::scale(model, glm::vec3(1.0f));
        model = glm::rotate(model, float(r.new_int32() % 360), glm::vec3(r.new_int32() / 1000.0f, r.new_int32() / 1000.0f, r.new_int32() / 1000.0f));

        poly.new_instance(model);
    }

    engine::event_manager->EVENT_SUBSCRIBE(engine::WindowResizeEvent, MainMenu::on_window_resize);
    engine::event_manager->EVENT_SUBSCRIBE(engine::KeyActionEvent, MainMenu::on_key_action);
}

MainMenu::~MainMenu() {

}

void MainMenu::on_connect() {

}

void MainMenu::on_disconnect() {

}

glm::vec2 last_mouse_pos;
void MainMenu::update() {
    if (application->window.get_key(GLFW_KEY_W) == GLFW_PRESS) {
        camera.translate(glm::vec3(1, 0, 0));
    }

    if (application->window.get_key(GLFW_KEY_S) == GLFW_PRESS) {
        camera.translate(glm::vec3(-1, 0, 0));
    }

    if (application->window.get_key(GLFW_KEY_A) == GLFW_PRESS) {
        camera.translate(glm::vec3(0, 0, -1));
    }

    if (application->window.get_key(GLFW_KEY_D) == GLFW_PRESS) {
        camera.translate(glm::vec3(0, 0, 1));
    }

    if (application->window.get_key(GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.translate(glm::vec3(0, 1, 0));
    }

    if (application->window.get_key(GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        camera.translate(glm::vec3(0, -1, 0));
    }

    if (application->window.get_key(GLFW_KEY_Q) == GLFW_PRESS) {
        camera.rotate(1.0f / 100.0f, glm::vec3(0, 0, 1));
    }

    if (application->window.get_key(GLFW_KEY_E) == GLFW_PRESS) {
        camera.rotate(-1.0f / 100.0f, glm::vec3(0, 0, 1));
    }

    glm::vec2 rot = application->window.get_mouse_pos() - last_mouse_pos;

    camera.rotate(rot.x / 1000.0f, glm::vec3(0, 1, 0));
    camera.rotate(rot.y / 1000.0f, glm::vec3(1, 0, 0));

    last_mouse_pos = application->window.get_mouse_pos();

	material.use();

    material.set_mat4("camera", camera.get_projection());

	poly.draw();
}

bool MainMenu::on_window_resize(const engine::WindowResizeEvent* e) {
    camera.set_perspective(45.0f, float(e->size.x), float(e->size.y), 0.1f, 1000000.0f);

    return false;
}

bool mouse_toggle;
bool MainMenu::on_key_action(const engine::KeyActionEvent* e) {
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