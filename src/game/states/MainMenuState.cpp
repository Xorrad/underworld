#include "MainMenuState.hpp"
#include "game/Game.hpp"

MainMenuState::MainMenuState(Game* game) : GameState(game) {}

void MainMenuState::Update() {
    tuim::Update(tuim::PollKeyCode());

    if (tuim::IsKeyPressed(tuim::F1))
        m_Game->SetRunning(false);
}

void MainMenuState::Render() {
    tuim::Clear();

    tuim::BeginContainer("#screen", "", tuim::Terminal::GetTerminalSize(), tuim::CONTAINER_FLAGS_BORDERLESS, tuim::ALIGN_CENTER);

    tuim::BeginContainer("#container", "", tuim::vec2(30, 10), tuim::CONTAINER_FLAGS_NONE, tuim::ALIGN_CENTER);
    tuim::Print("main\n");
    time_t timestamp = time(0);
    tuim::Print("{}", timestamp);
    tuim::EndContainer();
    
    tuim::EndContainer();

    tuim::Display();
}