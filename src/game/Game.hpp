#pragma once

#include "game/states/State.hpp"

class Game {
public:
    Game();

    bool IsRunning() const;

    void SetGameState(UniquePtr<State> gameState);
    void SetRunning(bool running);

    void Init(int argc, char* argv[]);
    void Run();
    void Exit();

private:
    std::vector<const char*> m_Args;
    UniquePtr<State> m_GameState;
    bool m_IsRunning;
};