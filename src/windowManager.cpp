//
// Created by Lenovo on 2022/12/13.
//

#include "windowManager.h"
#include <iostream>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#define SHADER_PATH "..\\src\\shaders\\"

windowManager::windowManager() {

};

float windowManager::lastX = SCR_HEIGHT / 2.0f;
float windowManager::lastY = SCR_WIDTH / 2.0f;
bool windowManager::firstMouse = true;
float windowManager::deltaTime = 0.0f;
float windowManager::lastFrame = 0.0f;
Camera windowManager::camera(glm::vec3(0.0f, 0.0f, 3.0f));
const float windowManager::cube[];

int windowManager::createWindow(int w, int h) {

    window = glfwCreateWindow(w, h, "LiqSurface", nullptr, nullptr);
    if (window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);

    BlinnPhongShader = new Shader("blinn_phong_vs.glsl", "blinn_phong_fs.glsl", SHADER_PATH);
    lightingCubeShader = new Shader("light_vs.glsl", "light_fs.glsl", SHADER_PATH);

    glGenVertexArrays(1, &centerCubeVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);
    glBindVertexArray(centerCubeVAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return 0;
}

void windowManager::renderLoop() {
    // TODO: change lightPos with imgui
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    while(!glfwWindowShouldClose(window)){
        auto currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 model(1.0f);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        BlinnPhongShader->use();
        // TODO: change colors with imgui
        BlinnPhongShader->setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        BlinnPhongShader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        BlinnPhongShader->setVec3("lightPos", lightPos);
        BlinnPhongShader->setVec3("viewPos", camera.Position);
        BlinnPhongShader->setMat4("model", model);
        BlinnPhongShader->setMat4("projection", projection);
        BlinnPhongShader->setMat4("view", view);
        glBindVertexArray(centerCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightingCubeShader->use();
        lightingCubeShader->setMat4("projection", projection);
        lightingCubeShader->setMat4("view", view);
        model = glm::mat4(1.0f);
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

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void windowManager::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void windowManager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void windowManager::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    auto xpos = static_cast<float>(xposIn);
    auto ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void windowManager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
