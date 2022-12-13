//
// Created by Lenovo on 2022/12/13.
//

#include "windowManager.h"
#include <iostream>

windowManager::windowManager() = default;

int windowManager::createWindow(int w, int h) {
    window = glfwCreateWindow(w, h, "LiqSurface", nullptr, nullptr);
    if (window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    return 0;
}

void windowManager::renderLoop() {
    while(!glfwWindowShouldClose(window)){
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
