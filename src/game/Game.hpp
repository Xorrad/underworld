#pragma once

class Game {
public:
    Game();

    void Init(int argc, char* argv[]);
    void Run();
    void Exit();

private:
    std::vector<const char*> m_Args;
};