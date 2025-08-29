#include "NewGameMenu.hpp"
#include "game/Game.hpp"
#include "game/core/world/World.hpp"
#include "game/core/world/Scenario.hpp"
#include "game/core/world/Country.hpp"
#include "game/core/world/State.hpp"
#include "game/core/world/City.hpp"
#include "game/states/IState.hpp"
#include "game/states/InGameState.hpp"
#include "game/ui/components/Components.hpp"

#include <fmt/format.h>

UI::NewGameMenu::NewGameMenu(Game* game, IState* state) : IMenu(game, state) {}

void UI::NewGameMenu::Update(bool skipInput) {
    tuim::Update((skipInput ? 0 : tuim::PollKeyCode()));

    if (tuim::IsKeyPressed(tuim::BACKSPACE))
        m_State->PopMenu();
}

void UI::NewGameMenu::Render() {
    tuim::Clear();

    tuim::BeginContainer("#screen", "", tuim::Terminal::GetTerminalSize(), tuim::CONTAINER_FLAGS_BORDERLESS, tuim::ALIGN_MIDDLE);

    tuim::BeginContainer("#container", "", tuim::vec2(tuim::Terminal::GetTerminalSize().x, 20), tuim::CONTAINER_FLAGS_BORDERLESS);
    tuim::Print("Underworld: Organized Crime\n#666666Version {}&r\n\n", Configuration::buildVersion);
    tuim::Print("New Game\n");
    
    std::vector<UniquePtr<Scenario>> scenarios = Scenario::ListScenarios();
    static size_t selectedScenario = 0;
    tuim::Print("\t");
    if (tuim::ScenarioInput("#input-scenario", "Scenario: < {} >", &selectedScenario, scenarios));
    tuim::Print("\n\n\t");
    
    if (tuim::Button("#button-start", "Start"))
        m_Game->SetState(MakeUnique<InGameState>(m_Game, MakeUnique<World>(std::move(scenarios[selectedScenario]))));
    tuim::Print("\n\t");

    if (tuim::Button("#button-back", "Back"))
        m_State->PopMenu();

    tuim::EndContainer();
    
    tuim::EndContainer();

    tuim::Display();
}