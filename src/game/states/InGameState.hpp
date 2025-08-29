#pragma once

#include "game/states/IState.hpp"

class InGameState : public IState {
public:
    InGameState(Game* game, UniquePtr<World> world);

    World* GetWorld();
    int GetGameSpeed() const;

    void Update() override;

private:
    UniquePtr<World> m_World;
    int m_GameSpeed;
};