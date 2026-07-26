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
#include "enemy.h"
#include "tilemap.h"
#include "damage_registry.h"
#include "bullet_system.h"

#include "context.h"

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

    // Context
    Context ctx;

    // Game state
    GameFsm gameFsm;
    ctx.gameFsm = &gameFsm;

    // Ui
    UiManager uiManager;
    uiManager.init(window, &gameFsm);
    ctx.uiManager = &uiManager;

    // Core
    AssetLibrary assetLibrary;
    ctx.assetLibrary = &assetLibrary;

    CollisionManager collisionManager;
    ctx.collisionManager = &collisionManager;

    Camera2 camera;
    ctx.camera2 = &camera;

    Scene scene{collisionManager, assetLibrary};
    ctx.scene = &scene;

    Input input(window);
    ctx.input = &input;

    // Features
    DamageRegistry damageRegistry;
    ctx.damageRegistry = &damageRegistry;

    BulletSystem bulletSystem{collisionManager, damageRegistry};
    ctx.bulletSystem = &bulletSystem;

    Tilemap tilemap{ctx};
    tilemap.load();
    Player player{ctx};
    Enemy enemy{ctx};

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

        // Input
        input.update();

        // Features
        player.update(deltaTime);
        enemy.update(deltaTime);

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