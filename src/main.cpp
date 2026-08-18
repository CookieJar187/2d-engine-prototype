#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "world.h"
#include "input.h"
#include "scene.h"
#include "camera.h"
#include "ui_manager.h"
#include "collision_manager.h"
#include "game_fsm.h"
#include "resource_manager.hpp"

#include "game_assets.hpp"
#include "player.h"
#include "enemy.h"
#include "tilemap.h"
#include "damage_registry.h"
#include "bullet_system.h"
#include "character_manager.hpp"

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

    // Ui
    UiManager uiManager;
    uiManager.init(window, &gameFsm);

    // Core
    ResourceManager resourceManager;
    World world;
    CollisionManager collisionManager{world};
    Camera2 camera;
    Scene scene{world, resourceManager};
    Input input(window);

    // Features
    GameAssets gameAssets{resourceManager};
    DamageRegistry damageRegistry;
    BulletSystem bulletSystem{collisionManager, damageRegistry, scene};

    Tilemap tilemap{scene};
    tilemap.load();

    CharacterManager characterManager{
        scene,
        input,
        camera,
        collisionManager,
        bulletSystem,
        damageRegistry,
        resourceManager,
        tilemap
    };
    characterManager.spawnPlayer();
    characterManager.spawnEnemy();

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
        bulletSystem.update(deltaTime);
        characterManager.update(deltaTime);

        // Draw game
        glClear(GL_COLOR_BUFFER_BIT);
        scene.cleanupObjects();
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