#pragma once

#include "game/states/IState.hpp"

class InGameState : public IState {
public:
    InGameState(Game* game, UniquePtr<World> world);

    World* GetWorld();
    int GetGameSpeed() const;
    Vec2<int> GetCursor() const;

    void SetCursor(Vec2<int> cursor);

    void Update() override;

private:
    UniquePtr<World> m_World;
    int m_GameSpeed;
    Vec2<int> m_Cursor;
};