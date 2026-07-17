#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input.h"
#include "scene.h"
#include "camera2.h"
#include "ui_manager.h"
#include "collision_manager.h"

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
    glfwSwapInterval(1);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr << "Failed to inialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    // Managers
    UiManager uiManager;
    CollisionManager collisionManager;
    uiManager.init(window);

    // Main items
    Scene scene(collisionManager);
    Input input(window);
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

        // Features
        player.update(deltaTime);

        // Collisions
        collisionManager.update();

        // Draw game
        glClear(GL_COLOR_BUFFER_BIT);
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