#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game_fsm.h"

#include "main_menu.h"
#include "settings.h"
#include "level_selection.h"

class UiManager
{
private:
    GameFsm* gameFsm;

    MainMenu* mainMenu;
    Settings* settings;
    LevelSelection* levelSelection;

public:
    int init(GLFWwindow* window, GameFsm* gameFsm);
    void buildUi();
    void drawUi();
    void destroyUi();
};