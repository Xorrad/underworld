#pragma once

namespace UI {

class Menu {
public:
    Menu(Game* game, State* state) : m_Game(game), m_State(state) {}
    virtual ~Menu() {}

    virtual void Update(bool skipInput = false) = 0;
    virtual void Render() = 0;

protected:
    Game* m_Game;
    State* m_State;
};

}