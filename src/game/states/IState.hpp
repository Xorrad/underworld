#pragma once

class IState {
public:
    IState(Game* game);
    virtual ~IState();
    
    void PushMenu(UniquePtr<UI::IMenu> menu);
    void PopMenu();

    virtual void Update();
    virtual void Render();

protected:
    Game* m_Game;
    std::stack<UniquePtr<UI::IMenu>> m_Menus;
    bool m_FirstFrame;
};