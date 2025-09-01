#pragma once

namespace UI {

class IMenu {
public:
    IMenu(Game* game, IState* state) : m_Game(game), m_State(state) {}
    virtual ~IMenu() {}

    virtual void Update(char32_t key, bool skipInput = false) = 0;
    virtual void Render() = 0;

protected:
    Game* m_Game;
    IState* m_State;
};

}