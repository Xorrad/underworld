#pragma once

#include "game/states/IState.hpp"

class InGameState : public IState {
public:
    InGameState(Game* game, UniquePtr<World> world);

    World* GetWorld();

private:
    UniquePtr<World> m_World;
};