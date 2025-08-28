#include "HomeMenu.hpp"
#include "game/Game.hpp"
#include "game/ui/components/Components.hpp"

#include "game/ui/menus/home/SettingsMenu.hpp"
#include "game/ui/menus/home/NewGameMenu.hpp"

UI::HomeMenu::HomeMenu(Game* game, IState* state) : IMenu(game, state) {}

void UI::HomeMenu::Update(bool skipInput) {
    tuim::Update((skipInput ? 0 : tuim::PollKeyCode()));

    if (tuim::IsKeyPressed(tuim::BACKSPACE))
        m_Game->SetRunning(false);
}

void UI::HomeMenu::Render() {
    tuim::Clear();

    tuim::BeginContainer("#screen", "", tuim::Terminal::GetTerminalSize(), tuim::CONTAINER_FLAGS_BORDERLESS, tuim::ALIGN_MIDDLE);

    tuim::BeginContainer("#container", "", tuim::vec2(tuim::Terminal::GetTerminalSize().x, 20), tuim::CONTAINER_FLAGS_BORDERLESS);
    // tuim::Print("Underworld: Organized Crime\n\n");
    tuim::Print("Underworld: Organized Crime\n#666666Version {}&r\n\n", Configuration::buildVersion);
    
    tuim::Print("\t");
    if (tuim::HomeMenuButton("#button-newgame", "New Game"))
        m_State->PushMenu(MakeUnique<UI::NewGameMenu>(m_Game, m_State));
    tuim::Print("\n\t");
    if (tuim::HomeMenuButton("#button-load", "Load"));
    tuim::Print("\n\t");
    if (tuim::HomeMenuButton("#button-settings", "Settings"))
        m_State->PushMenu(MakeUnique<UI::SettingsMenu>(m_Game, m_State));
    tuim::Print("\n\t");
    if (tuim::HomeMenuButton("#button-exit", "Exit"))
        m_Game->SetRunning(false);

    tuim::EndContainer();
    
    tuim::EndContainer();

    tuim::Display();
}