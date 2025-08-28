#include "SettingsMenu.hpp"
#include "game/Game.hpp"
#include "game/states/IState.hpp"
#include "game/ui/components/Components.hpp"

UI::SettingsMenu::SettingsMenu(Game* game, IState* state) : IMenu(game, state) {}

void UI::SettingsMenu::Update(bool skipInput) {
    tuim::Update((skipInput ? 0 : tuim::PollKeyCode()));

    if (tuim::IsKeyPressed(tuim::BACKSPACE))
        m_State->PopMenu();
}

void UI::SettingsMenu::Render() {
    tuim::Clear();

    tuim::BeginContainer("#screen", "", tuim::Terminal::GetTerminalSize(), tuim::CONTAINER_FLAGS_BORDERLESS, tuim::ALIGN_MIDDLE);

    tuim::BeginContainer("#container", "", tuim::vec2(tuim::Terminal::GetTerminalSize().x, 20), tuim::CONTAINER_FLAGS_BORDERLESS);
    tuim::Print("Underworld: Organized Crime\n#666666Version {}&r\n\n", Configuration::buildVersion);
    tuim::Print("Settings\n");
    
    tuim::Print("\t");
    if (tuim::Checkbox("#checkbox-debugmode", "Debug Mode: {}", &Configuration::debugMode))
        Configuration::Save();
    tuim::Print("\n\t");
    if (tuim::Button("#button-back", "Back"))
        m_State->PopMenu();

    tuim::EndContainer();
    
    tuim::EndContainer();

    tuim::Display();
}