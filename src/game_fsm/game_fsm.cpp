#include "game_fsm.h"

GameFsm::GameFsm()
{ currState = GameState::MainMenu; }

GameState GameFsm::getState() const
{ return GameFsm::currState; }

bool GameFsm::isState(const GameState& newState) const
{ return GameFsm::currState == newState; }

void GameFsm::setState(const GameState& newState)
{ GameFsm::currState = newState; }