#pragma once
#include "game_fsm.h"

class Settings {
public:
    Settings(GameFsm* gameFsm);
    void buildUi();

private:
    GameFsm* gameFsm;
    static bool test;
};