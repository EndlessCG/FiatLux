#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "windowManager.h"

int window_length = 800;
int window_height = 600;
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
    if (main_window.createWindow(window_length, window_height) != 0){
        return -1;
    }
    main_window.renderLoop();
    main_window.destroy();
    return 0;
}
