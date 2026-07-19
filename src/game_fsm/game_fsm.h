#pragma once

enum class GameState {
    MainMenu,
    LevelSelection,
    Settings,
    Playing,
    PauseMenu,
    Quit
};

class GameFsm {
public:
    GameFsm();

    GameState getState() const;
    bool isState(const GameState& newState) const;
    void setState(const GameState& newState);

private:
    GameState currState;

};