#include "MapMenu.hpp"
#include "game/Game.hpp"
#include "game/core/world/World.hpp"
#include "game/states/InGameState.hpp"
#include "game/ui/components/Components.hpp"

#include <fmt/format.h>

UI::MapMenu::MapMenu(Game* game, IState* state) : IMenu(game, state) {}

void UI::MapMenu::Update(bool skipInput) {
    tuim::Update((skipInput ? 0 : tuim::PollKeyCode()));

    InGameState* state = static_cast<InGameState*>(m_State);
    if (tuim::IsKeyPressed(tuim::BACKSPACE)) {
        m_State->PopMenu();
        return;
    }
    
    if (tuim::IsKeyPressed(tuim::Z) || tuim::GetPressedKey() == 'Z') {
        Vec2<int> cursor = state->GetCursor();
        int movement = (tuim::GetPressedKey() == 'Z') ? 10 : 1;
        state->SetCursor({cursor.x, std::max(0, cursor.y-movement)});
    }
    else if (tuim::IsKeyPressed(tuim::S) || tuim::GetPressedKey() == 'S') {
        Vec2<int> cursor = state->GetCursor();
        int movement = (tuim::GetPressedKey() == 'S') ? 10 : 1;
        state->SetCursor({cursor.x, std::min((int) state->GetWorld()->GetStatesImage()->GetHeight()-1, cursor.y+movement)});
    }
    if (tuim::IsKeyPressed(tuim::Q) || tuim::GetPressedKey() == 'Q') {
        Vec2<int> cursor = state->GetCursor();
        int movement = (tuim::GetPressedKey() == 'Q') ? 10 : 1;
        state->SetCursor({std::max(0, cursor.x-movement), cursor.y});
    }
    else if (tuim::IsKeyPressed(tuim::D) || tuim::GetPressedKey() == 'D') {
        Vec2<int> cursor = state->GetCursor();
        int movement = (tuim::GetPressedKey() == 'D') ? 10 : 1;
        state->SetCursor({std::min((int) state->GetWorld()->GetStatesImage()->GetWidth()-1, cursor.x+movement), cursor.y});
    }
}

void UI::MapMenu::Render() {
    tuim::vec2 terminalSize = tuim::Terminal::GetTerminalSize();
    InGameState* state = static_cast<InGameState*>(m_State);
    World* world = static_cast<InGameState*>(m_State)->GetWorld();
    Vec2<int> cursor = state->GetCursor();

    tuim::Clear();
    tuim::BeginContainer("#screen", "", terminalSize, tuim::CONTAINER_FLAGS_BORDERLESS, tuim::ALIGN_NONE);

    tuim::Header(static_cast<InGameState*>(m_State));

    tuim::vec2 mapSize = {(int)(0.8f*terminalSize.x), terminalSize.y-UI::HEADER_HEIGHT+1};
    if (mapSize.x % 2 == 1) mapSize.x += 1;
    tuim::SetCurrentCursor({terminalSize.x-mapSize.x, UI::HEADER_HEIGHT-1});
    tuim::BeginContainer("#container-minimap", "", {mapSize.x, mapSize.y});
    {
        // All images should be the same size.
        ::Image* statesImage = world->GetStatesImage();
        ::Image* terrainImage = world->GetTerrainImage();
        auto& statesPixels = statesImage->GetPixels();
        auto& terrainPixels = terrainImage->GetPixels();
        auto& terrainCharacters = world->GetTerrain();

        ::Color previousColor = ::Color(0, 0, 0, 0);

        // Define the bounding box of the map.
        // It is rendered at real image size around the cursor.
        Vec2<int> origin = {
            std::min((int) terrainImage->GetWidth() - mapSize.x/2 + 1, std::max(0, cursor.x - mapSize.x/4)),
            std::min((int) terrainImage->GetHeight() - mapSize.y + 2, std::max(0, cursor.y - mapSize.y/2))
        };
        Vec2<int> end = { origin.x + mapSize.x, origin.y + mapSize.y };

        for (uint32_t y = origin.y; y < end.y; y++) {
            for (uint32_t x = origin.x; x < end.x; x++) {
                uint32_t index = y * terrainImage->GetWidth() + x;
                if (previousColor != terrainPixels[index]) {
                    previousColor = terrainPixels[index];
                    tuim::Print("#_" + previousColor.ToHex());
                }
                // tuim::Print("{}{}", terrainCharacters[y][2*x], terrainCharacters[y][2*x+1]);
                tuim::Print("  ");
            }
            tuim::Print("\n");
        }
        tuim::Print("&r");

        tuim::SetCurrentCursor({2*(cursor.x - origin.x), cursor.y - origin.y});
        tuim::Print("#_ffffff  &r");

        tuim::SetCurrentCursor({0, mapSize.y-3});
        tuim::Print("#_666666Press M to open map&r");
        
        std::string coordsText = fmt::format("#_666666({}, {})&r", state->GetCursor().x, state->GetCursor().y);
        tuim::SetCurrentCursor({mapSize.x - (int) tuim::CalcTextWidth(coordsText)+3, mapSize.y-3});
        tuim::Print(coordsText);
    }
    tuim::EndContainer();

    int titleHeight = 5;
    int sidebarWidth = terminalSize.x - mapSize.x;
    tuim::SetCurrentCursor({0, UI::HEADER_HEIGHT-1});
    tuim::BeginContainer("#container-title", "", {sidebarWidth+1, titleHeight}, tuim::CONTAINER_FLAGS_NONE, tuim::ALIGN_CENTER);
    tuim::BeginContainer("#container-title-inner", "", {(int) tuim::CalcTextWidth("Empty Desert"), titleHeight}, tuim::CONTAINER_FLAGS_BORDERLESS);
    tuim::Print("\nEmpty Desert");
    tuim::EndContainer();
    tuim::EndContainer();

    tuim::SetCurrentCursor({0, UI::HEADER_HEIGHT+titleHeight-2});
    tuim::BeginContainer("#container-sidebar", "", {sidebarWidth+1, terminalSize.y-UI::HEADER_HEIGHT-titleHeight+2});
    
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
    if (tuim::HomeMenuButton("#button-back", "Back"))
        m_State->PopMenu();
        
    tuim::EndContainer();
    
    tuim::EndContainer();
    tuim::Display();
}