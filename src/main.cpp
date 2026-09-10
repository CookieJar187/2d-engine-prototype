#include "core.hpp"
#include "features.hpp"

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

    UiManager uiManager;
    uiManager.init(window, &gameFsm);

    Core core{window};
    Features features{core};

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
            //features.characterManager.spawnEnemy({rng::getInt(9) * 100, 0});
            //characterManager.spawnComrade({rng::getInt(9) * 100, -900});
            TEM = 0;
        }
        else
            TEM += deltaTime;

        glfwPollEvents();
        uiManager.buildUi();

        core.input.update();
        features.update(deltaTime, elapsed);

        // Draw game
        glClear(GL_COLOR_BUFFER_BIT);
        core.scene.cleanupObjects();
        core.renderer.drawObjects(core.camera.getViewMatrix(), core.camera.projection);
        
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