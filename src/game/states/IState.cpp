#include "IState.hpp"
#include "game/ui/menus/IMenu.hpp"

IState::IState(Game* game) :
    m_Game(game),
    m_Menus(),
    m_FirstFrame(false)
{}

IState::~IState() {}

void IState::PushMenu(UniquePtr<UI::IMenu> menu) {
    m_Menus.push(std::move(menu));
    m_FirstFrame = true;
}

void IState::PopMenu() {
    if (m_Menus.empty())
        return;
    m_Menus.pop();
    m_FirstFrame = true;
}

void IState::Update() {
    if (m_Menus.empty())
        return;
    char32_t key = (m_FirstFrame ? 0 : tuim::PollKeyCode());
    m_Menus.top()->Update(key, m_FirstFrame);
}

void IState::Render() {
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