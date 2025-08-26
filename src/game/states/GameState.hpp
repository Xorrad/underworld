#pragma once

class GameState {
public:
    GameState(Game* game) : m_Game(game) {}
    virtual ~GameState() {}

    virtual void Update() = 0;
    virtual void Render() = 0;

protected:
    Game* m_Game;
};