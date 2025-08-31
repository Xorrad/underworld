#include "OverviewMenu.hpp"
#include "game/Game.hpp"
#include "game/core/world/World.hpp"
#include "game/states/InGameState.hpp"
#include "game/ui/components/Components.hpp"
#include "game/states/HomeState.hpp"
#include "game/ui/menus/ingame/MapMenu.hpp"

UI::OverviewMenu::OverviewMenu(Game* game, IState* state) : IMenu(game, state) {}

void UI::OverviewMenu::Update(bool skipInput) {
    tuim::Update((skipInput ? 0 : tuim::PollKeyCode()));

    if (tuim::IsKeyPressed(tuim::BACKSPACE)) {
        dynamic_cast<InGameState*>(m_State)->SetExitToHomeMenu(true);
        return;
    }
    
    if (tuim::IsKeyPressed(tuim::M)) {
        m_State->PushMenu(MakeUnique<UI::MapMenu>(m_Game, m_State));
        return;
    }
}

void UI::OverviewMenu::Render() {
    tuim::vec2 terminalSize = tuim::Terminal::GetTerminalSize();

    tuim::Clear();
    tuim::BeginContainer("#screen", "", terminalSize, tuim::CONTAINER_FLAGS_BORDERLESS, tuim::ALIGN_NONE);

    tuim::Header(static_cast<InGameState*>(m_State));
    
    tuim::vec2 minimapSize = {(int) (2 * 80 * ((float) (terminalSize.y-UI::HEADER_HEIGHT+1) / 52.f))+2, terminalSize.y-UI::HEADER_HEIGHT+1};
    tuim::SetCurrentCursor({terminalSize.x-minimapSize.x, UI::HEADER_HEIGHT-1});
    tuim::Minimap("#container-minimap", minimapSize, static_cast<InGameState*>(m_State)->GetWorld());

    int alertsHeight = 10;
    tuim::SetCurrentCursor({0, terminalSize.y-alertsHeight});
    tuim::BeginContainer("#container-alerts", "", {terminalSize.x-minimapSize.x+1, alertsHeight});
    tuim::Print("One of your warehouse in Sinaloa has been raided!");
    tuim::EndContainer();

    tuim::SetCurrentCursor({0, UI::HEADER_HEIGHT-1});
    tuim::BeginContainer("#container-menus", "", {terminalSize.x-minimapSize.x+1, terminalSize.y-UI::HEADER_HEIGHT-alertsHeight+2});
    tuim::Print("Underworld: Organized Crime\n#666666Version {}&r\n\n", Configuration::buildVersion);
    
    tuim::Print("\t");
    if (tuim::HomeMenuButton("#button-buildings", "Buildings"));

    tuim::Print("\n\t");
    if (tuim::HomeMenuButton("#button-intrigue", "Intrigue"));
    
    tuim::Print("\n\t");
    if (tuim::HomeMenuButton("#button-members", "Members"));
    
    tuim::Print("\n\t");
    if (tuim::HomeMenuButton("#button-finances", "Finances"));
    
    tuim::Print("\n\t");
    if (tuim::HomeMenuButton("#button-diplomacy", "Diplomacy"));

    tuim::Print("\n\t");
    if (tuim::HomeMenuButton("#button-registry", "Registry"));
    
    tuim::Print("\n\t");
    if (tuim::HomeMenuButton("#button-ledger", "Ledger"));

    tuim::Print("\n\n\t");
    if (tuim::HomeMenuButton("#button-exit", "Exit"))
        m_Game->SetState(MakeUnique<HomeState>(m_Game));
        
    tuim::EndContainer();
    
    tuim::EndContainer();
    tuim::Display();
}