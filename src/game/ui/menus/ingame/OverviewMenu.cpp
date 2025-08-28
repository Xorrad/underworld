#include "OverviewMenu.hpp"
#include "game/Game.hpp"
#include "game/ui/components/Components.hpp"

#include "game/states/HomeState.hpp"

UI::OverviewMenu::OverviewMenu(Game* game, IState* state) : IMenu(game, state) {}

void UI::OverviewMenu::Update(bool skipInput) {
    tuim::Update((skipInput ? 0 : tuim::PollKeyCode()));

    if (tuim::IsKeyPressed(tuim::BACKSPACE)) {
        m_Game->SetState(MakeUnique<HomeState>(m_Game));
        return;
    }
}

void UI::OverviewMenu::Render() {
    tuim::vec2 terminalSize = tuim::Terminal::GetTerminalSize();
    int headerHeight = 6;
    int alertsHeight = 10;
    tuim::vec2 minimapSize = {(int) (80 * 52.f/terminalSize.y)+2, terminalSize.y-headerHeight+1}; //80, 52

    tuim::Clear();
    tuim::BeginContainer("#screen", "", terminalSize, tuim::CONTAINER_FLAGS_BORDERLESS, tuim::ALIGN_NONE);

    tuim::BeginContainer("#container-header", "", {terminalSize.x, headerHeight});
    tuim::Print("\n");
    tuim::SetCurrentCursor({1, 1}); tuim::Print("Your Organization Name");
    tuim::SetCurrentCursor({1, 2}); tuim::Print("Money: $2.5M / $11.2M");
    tuim::SetCurrentCursor({30, 2}); tuim::Print("Members: 52");
    tuim::SetCurrentCursor({50, 2}); tuim::Print("Territories: 5");
    tuim::SetCurrentCursor({terminalSize.x-2-11, 1}); tuim::Print("Speed #555555█&r███");
    tuim::SetCurrentCursor({terminalSize.x-2-20, 2}); tuim::Print("November 11th, 1987");
    tuim::EndContainer();
    
    tuim::SetCurrentCursor({terminalSize.x-minimapSize.x, headerHeight-1});
    tuim::BeginContainer("#container-minimap", "", minimapSize);
    tuim::EndContainer();

    tuim::SetCurrentCursor({0, terminalSize.y-alertsHeight});
    tuim::BeginContainer("#container-alerts", "", {terminalSize.x-minimapSize.x+1, alertsHeight});
    tuim::Print("One of your warehouse in Sinaloa has been raided!");
    tuim::EndContainer();

    tuim::SetCurrentCursor({0, headerHeight-1});
    tuim::BeginContainer("#container-menus", "", {terminalSize.x-minimapSize.x+1, terminalSize.y-headerHeight-alertsHeight+2});
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