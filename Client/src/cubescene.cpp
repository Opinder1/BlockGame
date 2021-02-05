#include "cubescene.h"

CubeScene::CubeScene() : camera(70.0f), cube_material("cube"), cube_poly(), camera_buf(0) {
    application->window.set_mouse_type(GLFW_CURSOR_DISABLED);

    camera_buf.set_data<glm::mat4>(1, nullptr, engine::BufferType::Static);

    engine::event_manager->EVENT_SUBSCRIBE(engine::KeyActionEvent, CubeScene::on_key_action);

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
    frame.clear({ 0.0, 0.0, 0.0, 0.0 });
    frame.set_depthtest(true);
    frame.set_alphatest(true);
    frame.set_multisample(true);
    frame.set_culling(engine::Culling::Back);

    float speed = 0.2;
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

    if (application->window.get_key(GLFW_KEY_Q) == GLFW_PRESS) {
        camera.rotation.z += 0.1;
    }

    if (application->window.get_key(GLFW_KEY_E) == GLFW_PRESS) {
        camera.rotation.z -= 0.1;
    }

    camera.update(application->window.get_mouse_pos());

    glm::mat4 p = camera.get_projection();
    camera_buf.modify_data(0, 1, &p);

    cube_material.use();

    for (auto& transform : transforms) {
        cube_material.set("transform", transform);

        cube_poly.draw();
    }
}

void CubeScene::move_camera(glm::vec3 translation) {
    translation = glm::rotate(translation, -camera.rotation.x, camera.up_direction());
    translation = glm::rotate(translation, -camera.rotation.y, camera.left_direction());
    camera.position += translation;
}

bool CubeScene::on_key_action(const engine::KeyActionEvent* e) {
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