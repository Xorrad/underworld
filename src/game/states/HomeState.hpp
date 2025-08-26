#pragma once

#include "game/states/State.hpp"

class HomeState : public State {
public:
    HomeState(Game* game);

    void Update() override;
    void Render() override;

private:
};