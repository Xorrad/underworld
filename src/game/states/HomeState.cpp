#include "HomeState.hpp"
#include "game/Game.hpp"

HomeState::HomeState(Game* game) : State(game) {}

void HomeState::Update() {
    tuim::Update(tuim::PollKeyCode());

    if (tuim::IsKeyPressed(tuim::F1))
        m_Game->SetRunning(false);
}

void HomeState::Render() {
    tuim::Clear();

    tuim::BeginContainer("#screen", "", tuim::Terminal::GetTerminalSize(), tuim::CONTAINER_FLAGS_BORDERLESS, tuim::ALIGN_CENTER);

    tuim::BeginContainer("#container", "", tuim::vec2(30, 10), tuim::CONTAINER_FLAGS_NONE, tuim::ALIGN_CENTER);
    tuim::Print("home state\n");
    time_t timestamp = time(0);
    tuim::Print("{}", timestamp);
    tuim::EndContainer();
    
    tuim::EndContainer();

    tuim::Display();
}