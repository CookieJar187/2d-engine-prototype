#pragma once
#include "game_fsm.h"

class LevelSelection {
public:
    LevelSelection(GameFsm* gameFsm);
    void buildUi();

private:
    GameFsm* gameFsm;
};