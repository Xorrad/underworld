#pragma once

#include "game/states/IState.hpp"

class Game {
public:
    Game();

    bool IsRunning() const;

    void SetState(UniquePtr<IState> state);
    void SetRunning(bool running);

    void Init(int argc, char* argv[]);
    void Run();
    void Exit();

private:
    std::vector<const char*> m_Args;
    UniquePtr<IState> m_State;
    bool m_IsRunning;
};