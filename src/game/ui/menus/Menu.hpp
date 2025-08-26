#pragma once

namespace UI {

class Menu {
public:
    Menu(Game* game, State* gameState) : m_Game(game), m_GameState(gameState) {}
    virtual ~Menu() {}

    virtual void Update() = 0;
    virtual void Render() = 0;

protected:
    Game* m_Game;
    State* m_GameState;
};

}