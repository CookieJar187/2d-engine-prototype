#include "core.hpp"

#include "game_assets.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "tilemap.h"
#include "damage_registry.h"
#include "bullet_system.h"
#include "explosion_system.hpp"
#include "grenade_system.hpp"
#include "melee_system.hpp"
#include "character_manager.hpp"
#include "rng.hpp"
#include "camera_shaker.hpp"

int main()
{
    // GLFW init
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

    // OpenAL
    ALCdevice* soundDevice = alcOpenDevice(nullptr);;

    if (!soundDevice)
        std::cerr << "ALCdevice failed to initialize" << std::endl;

    ALCcontext* soundContext = alcCreateContext(soundDevice, nullptr);

    if (!soundContext)
        alcCloseDevice(soundDevice);

    alcMakeContextCurrent(soundContext);

    // Game state
    GameFsm gameFsm;

    // Ui
    UiManager uiManager;
    uiManager.init(window, &gameFsm);

    // Core
    Core core{window};

    // Features
    GameAssets gameAssets{core};
    DamageRegistry damageRegistry;
    CameraShaker cameraShaker{core};
    BulletSystem bulletSystem{core, damageRegistry};
    ExplosionSystem explosionSystem{core, damageRegistry, cameraShaker};
    GrenadeSystem grenadeSystem{core, explosionSystem};
    MeleeSystem meleeSystem{core, damageRegistry};

    Tilemap tilemap{core, damageRegistry};
    tilemap.load();

    CharacterManager characterManager{
        core,
        bulletSystem,
        damageRegistry,
        tilemap,
        grenadeSystem,
        meleeSystem,
        cameraShaker
    };
    characterManager.spawnPlayer({500, -500});

    // Process
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    float elapsed = 0.0f;

    float MAX = 4;
    float TEM = 4;

    while (!glfwWindowShouldClose(window))
    {
        float currFrame = static_cast<float>(glfwGetTime());
        deltaTime = currFrame - lastFrame;
        lastFrame = currFrame;
        elapsed += deltaTime;

        if (TEM > MAX)
        {
            characterManager.spawnEnemy({rng::getInt(9) * 100, 0});
            TEM = 0;
        }
        else
            TEM += deltaTime;

        glfwPollEvents();
        uiManager.buildUi();

        // Input
        core.input.update();

        // Features
        bulletSystem.update(deltaTime);
        grenadeSystem.update(deltaTime);
        explosionSystem.update(deltaTime);
        meleeSystem.update(deltaTime);
        tilemap.update(deltaTime);
        characterManager.update(deltaTime);
        cameraShaker.update(elapsed);

        // Draw game
        glClear(GL_COLOR_BUFFER_BIT);
        core.scene.cleanupObjects();
        core.scene.drawObjects(core.camera.getViewMatrix(), core.camera.projection);
        
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