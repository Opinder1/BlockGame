#include "input.h"

namespace engine {
    void on_mouse_move(GLFWwindow* window, int event_width, int event_height) {
        ocode::EventManager* manager = (ocode::EventManager*)glfwGetWindowUserPointer(window);

        //manager->EVENT_POST(WindowResizeEvent, { (uint32)event_width, (uint32)event_height });
    }
}