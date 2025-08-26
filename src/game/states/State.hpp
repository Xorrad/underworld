#pragma once

class State {
public:
    State(Game* game);
    virtual ~State();
    
    void PushMenu(UniquePtr<UI::Menu> menu);
    void PopMenu();

    virtual void Update();
    virtual void Render();

protected:
    Game* m_Game;
    std::stack<UniquePtr<UI::Menu>> m_Menus;
};