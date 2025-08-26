#include "State.hpp"
#include "game/ui/menus/Menu.hpp"

State::State(Game* game) : m_Game(game), m_Menus() {}

State::~State() {}

void State::PushMenu(UniquePtr<UI::Menu> menu) {
    m_Menus.push(std::move(menu));
}

void State::PopMenu() {
    if (m_Menus.empty())
        return;
    m_Menus.pop();
}

void State::Update() {
    if (m_Menus.empty())
        return;
    m_Menus.top()->Update();
}

void State::Render() {
    if (m_Menus.empty())
        return;
    m_Menus.top()->Render();
}