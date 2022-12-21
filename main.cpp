#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "windowManager.h"

void initGL(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

int main() {
    initGL();
    windowManager main_window;
    GLFWmonitor* pMonitor = glfwGetPrimaryMonitor();
    auto mode = glfwGetVideoMode(pMonitor);
    if (main_window.createWindow(mode->width, mode->height) != 0){
        return -1;
    }
    main_window.renderLoop();
    main_window.destroy();
    return 0;
}
