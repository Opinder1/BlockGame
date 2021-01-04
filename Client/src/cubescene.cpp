#include "cubescene.h"

void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    //fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

CubeScene::CubeScene() : camera(70.0f), material("polygon3d"), poly("none", &material) {
    printf("GL Version: %s\n", glGetString(GL_VERSION));
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    int count = 10000000;
    float size = sqrt(count) * 2;

    for (int i = 0; i < count; i++) {
        glm::mat4 model = glm::mat4(1.0f);

        float p1 = map(float(r.new_int32()), float(INT32_MIN), float(INT32_MAX), -size, size);
        float p2 = map(float(r.new_int32()), float(INT32_MIN), float(INT32_MAX), -size, size);

        model = glm::translate(model, glm::vec3(p1, 0, p2));
        model = glm::scale(model, glm::vec3(1.0f));
        model = glm::rotate(model, float(r.new_int32() % 360), glm::vec3(r.new_int32() / 1000.0f, r.new_int32() / 1000.0f, r.new_int32() / 1000.0f));

        poly.new_instance(model);
    }

    application->window.set_mouse_type(GLFW_CURSOR_DISABLED);

    engine::event_manager->EVENT_SUBSCRIBE(engine::KeyActionEvent, CubeScene::on_key_action);
}

CubeScene::~CubeScene() {

}

void CubeScene::on_connect() {

}

void CubeScene::on_disconnect() {

}

void CubeScene::update() {
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

    for (int i = 0; i < 0; i++) {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(cos(tick) * sqrt(tick) * 2, -10, sin(tick) * sqrt(tick) * 2));
        model = glm::scale(model, glm::vec3(1.0f));
        model = glm::rotate(model, float(r.new_int32() % 360), glm::vec3(r.new_int32() / 1000.0f, r.new_int32() / 1000.0f, r.new_int32() / 1000.0f));

        poly.new_instance(model);

        tick++;
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