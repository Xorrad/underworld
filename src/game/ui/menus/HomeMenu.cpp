#include "HomeMenu.hpp"
#include "game/Game.hpp"
#include "game/ui/components/Components.hpp"

UI::HomeMenu::HomeMenu(Game* game, State* state) : Menu(game, state) {}

void UI::HomeMenu::Update() {
    tuim::Update(tuim::PollKeyCode());

    if (tuim::IsKeyPressed(tuim::F1))
        m_Game->SetRunning(false);
}

void UI::HomeMenu::Render() {
    tuim::Clear();

    tuim::BeginContainer("#screen", "", tuim::Terminal::GetTerminalSize(), tuim::CONTAINER_FLAGS_BORDERLESS, tuim::ALIGN_MIDDLE);

    tuim::BeginContainer("#container", "", tuim::vec2(tuim::Terminal::GetTerminalSize().x, 20), tuim::CONTAINER_FLAGS_BORDERLESS);
    // tuim::Print("Underworld: Organized Crime\n\n");
    tuim::Print("Underworld: Organized Crime\n#666666Version 1.0.0&r\n\n");
    
    tuim::Print("\t");
    if (tuim::HomeMenuButton("#button-newgame", "New Game"));
    tuim::Print("\n\t");
    if (tuim::HomeMenuButton("#button-load", "Load"));
    tuim::Print("\n\t");
    if (tuim::HomeMenuButton("#button-settings", "Settings"));
    tuim::Print("\n\t");
    if (tuim::HomeMenuButton("#button-exit", "Exit"))
        m_Game->SetRunning(false);

    tuim::EndContainer();
    
    tuim::EndContainer();

    tuim::Display();
}