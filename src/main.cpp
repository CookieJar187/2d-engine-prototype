#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "input.h"
#include "scene.h"
#include "camera2.h"
#include "ui_manager.h"

#include "player.h"

int main() {

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600,"OpenGL Window",nullptr,nullptr);

    if (!window)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr << "Failed to inialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    // Ui
    UiManager uiManager;
    uiManager.init(window);

    // Main items
    Input input(window);
    Scene scene;
    Player player;
    player.init(scene, input);

    // Process
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currFrame = static_cast<float>(glfwGetTime());
        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;

        glfwPollEvents();
        uiManager.buildUi();

        // Draw game
        glClear(GL_COLOR_BUFFER_BIT);
        player.update(deltaTime);
        scene.drawObjects();

        // Draw ui
        uiManager.drawUi();
        glfwSwapBuffers(window);
    }
    uiManager.destroyUi();

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}