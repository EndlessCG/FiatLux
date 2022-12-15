//
// Created by Lenovo on 2022/12/13.
//

#include "windowManager.h"
#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#define SCR_WIDTH 800
#define SCR_HEIGHT 600

windowManager::windowManager() {
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &centerCubeVAO);
    glGenVertexArrays(1, &lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
    glBindVertexArray(centerCubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(lightCubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    BlinnPhongShader = new Shader("bp_vs.glsl", "bp_fs.glsl");
    lightingCubeShader = new Shader("lux_vs.glsl", "lux_fs.glsl");
};

int windowManager::createWindow(int w, int h) {
    window = glfwCreateWindow(w, h, "LiqSurface", nullptr, nullptr);
    if (window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glfwMakeContextCurrent(window);
    return 0;
}

void windowManager::renderLoop() {
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        BlinnPhongShader->use();
        // TODO: change colors with imgui
        BlinnPhongShader->setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        BlinnPhongShader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        BlinnPhongShader->setMat4("model", glm::mat4(1.0f));
        glBindVertexArray(centerCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        auto projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        auto view = camera.GetViewMatrix();
        lightingCubeShader->use();
        lightingCubeShader->setMat4("projection", projection);
        lightingCubeShader->setMat4("view", view);

        // TODO: change lightPos with imgui
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        auto model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightingCubeShader->setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void windowManager::destroy() {
    glDeleteVertexArrays(1, &centerCubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
}
