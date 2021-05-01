#include "cubescene.h"

CubeScene::CubeScene() : camera(70.0f, application->window.get_size()), surface(application->window.get_size(), 32), cube_material("cube"), cube_poly() {
    application->window.set_mouse_type(GLFW_CURSOR_DISABLED);

    camera_buffer.set_data<glm::mat4>(1, nullptr, engine::BufferType::Static);

    engine::event_manager->event_subscribe(engine::KeyActionEvent, on_key_action);
    engine::event_manager->event_subscribe(engine::WindowResizeEvent, on_window_resize);

    int count = 10000;
    float size = (float)sqrt(count) * 2;
     
    for (int i = 0; i < count; i++) {
        glm::mat4 model = glm::mat4(1.0f);

        float p1 = map(float(r.new_int32()), float(INT32_MIN), float(INT32_MAX), -size, size);
        float p2 = map(float(r.new_int32()), float(INT32_MIN), float(INT32_MAX), -size, size);

        model = glm::translate(model, glm::vec3(p1, 0, p2));
        model = glm::scale(model, glm::vec3(1.0f));
        model = glm::rotate(model, float(r.new_int32() % 360), glm::vec3(r.new_int32() / 1000.0f, r.new_int32() / 1000.0f, r.new_int32() / 1000.0f));

        transforms.push_back(model);
    }
}

CubeScene::~CubeScene() { 
     
} 

void CubeScene::update() {
    float speed = 0.2f;
    if (application->window.get_key(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        speed *= 5.0f;
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

    if (application->window.get_key(GLFW_KEY_Q) == GLFW_PRESS) {
        camera.rotation.z += 0.1f;
    }

    if (application->window.get_key(GLFW_KEY_E) == GLFW_PRESS) {
        camera.rotation.z -= 0.1f;
    }

    camera.update(application->window.get_mouse_pos());

    glm::mat4 p = camera.get_projection();
    camera_buffer.modify_data(0, 1, &p);
    camera_buffer.activate_slot(0);

    engine::set_multisample(true);
    engine::set_alphatest(true);
    engine::set_depthtest(true);
    engine::set_culling(engine::Culling::Back);

    surface.clear();

    cube_material.use();

    for (auto& transform : transforms) {
        cube_material.set("transform", transform);

        cube_poly.draw();
    }

    application->surface.draw(surface.texture);
}

void CubeScene::move_camera(glm::vec3 translation) {
    translation = glm::rotate(translation, -camera.rotation.x, camera.up_direction());
    translation = glm::rotate(translation, -camera.rotation.y, camera.left_direction());
    camera.position += translation;
}

void CubeScene::on_key_action(const engine::KeyActionEvent* e) {
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

void CubeScene::on_window_resize(const engine::WindowResizeEvent* e) {
    surface.resize(e->size, 32);
}