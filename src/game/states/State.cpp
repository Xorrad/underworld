#include "State.hpp"
#include "game/ui/menus/Menu.hpp"

State::State(Game* game) :
    m_Game(game),
    m_Menus(),
    m_FirstFrame(false)
{}

State::~State() {}

void State::PushMenu(UniquePtr<UI::Menu> menu) {
    m_Menus.push(std::move(menu));
    m_FirstFrame = true;
}

void State::PopMenu() {
    if (m_Menus.empty())
        return;
    m_Menus.pop();
    m_FirstFrame = true;
}

void State::Update() {
    if (m_Menus.empty())
        return;
    m_Menus.top()->Update(m_FirstFrame);
}

void State::Render() {
    if (m_Menus.empty())
        return;
    
    // The first frame need to be rendered and then updated in order for
    // tuim to map out the items in the frame and which are hovered.
    if (m_FirstFrame) {
        m_Menus.top()->Render();
        this->Update();
    }
    m_FirstFrame = false;

    m_Menus.top()->Render();
}