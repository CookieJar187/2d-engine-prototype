#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <al.h>
#include <alc.h>

#include "world.h"
#include "input.h"
#include "scene.h"
#include "camera.h"
#include "ui_manager.h"
#include "collision.hpp"
#include "game_fsm.h"
#include "resource_manager.hpp"

class Core
{
private:
    GLFWwindow *window;

public:
    Core(GLFWwindow *window) : window(window) {}

    ResourceManager resourceManager;
    World world;
    Collision collision{world};
    Camera2 camera;
    Scene scene{world, resourceManager};
    Input input{this->window};
};