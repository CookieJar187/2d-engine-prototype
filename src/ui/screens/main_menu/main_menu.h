#pragma once
#include "game_fsm.h"

class MainMenu {
public:
    MainMenu(GameFsm* gameFsm);
    void buildUi();

private:
    GameFsm* gameFsm;
};