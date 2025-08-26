#pragma once

#include "game/states/GameState.hpp"

class MainMenuState : public GameState {
public:
    MainMenuState(Game* game);

    void Update() override;
    void Render() override;

private:
};