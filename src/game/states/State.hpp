#pragma once

class State {
public:
    State(Game* game) : m_Game(game) {}
    virtual ~State() {}

    virtual void Update() = 0;
    virtual void Render() = 0;

protected:
    Game* m_Game;
};