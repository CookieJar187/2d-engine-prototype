#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input.h"
#include "scene.h"
#include "camera2.h"
#include "ui_manager.h"
#include "collision_manager.h"
#include "game_fsm.h"
#include "asset_library.h"

#include "player.h"
#include "tilemap.h"

int main()
{

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);

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

    // Game state
    GameFsm gameFsm;

    // Managers
    AssetLibrary assetLibrary;
    UiManager uiManager;
    uiManager.init(window, &gameFsm);

    CollisionManager collisionManager;

    // Main items
    Camera2 camera;
    Scene scene{collisionManager, assetLibrary};
    Input input(window);
    Tilemap tilemap{scene};
    tilemap.load();
    Player player{scene, input, collisionManager, camera};

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

        // Draw game
        glClear(GL_COLOR_BUFFER_BIT);
        scene.drawObjects(camera.getViewMatrix(), camera.projection);

        // Draw ui
        uiManager.drawUi();
        glfwSwapBuffers(window);

        // Check if user wants to quit
        if (gameFsm.isState(GameState::Quit))
            break;
    }
    uiManager.destroyUi();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}