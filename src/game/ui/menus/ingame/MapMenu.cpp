#include "MapMenu.hpp"
#include "game/Game.hpp"
#include "game/core/Includes.hpp"
#include "game/states/InGameState.hpp"
#include "game/ui/components/Components.hpp"

#include <fmt/format.h>

UI::MapMenu::MapMenu(Game* game, IState* state) : IMenu(game, state) {}

void UI::MapMenu::Update(char32_t key, bool skipInput) {
    tuim::Update(key);

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

        auto& buildings = world->GetBuildings();

        for (int y = origin.y; y < end.y; y++) {
            for (int x = origin.x; x < end.x; x++) {
                uint32_t index = y * terrainImage->GetWidth() + x;

                auto it = buildings.find({x, y});
                if (it != buildings.end()) {
                    tuim::Print("#_666666{} &r", it->second->GetType()->GetIcon());
                }
                else {
                    if (previousColor != terrainPixels[index]) {
                        previousColor = terrainPixels[index];
                        tuim::Print("#_" + previousColor.ToHex());
                    }
                    tuim::Print("  ");
                    // tuim::Print("{}{}", terrainCharacters[y][2*x], terrainCharacters[y][2*x+1]);
                }
            }
            tuim::Print("\n");
        }
        tuim::Print("&r");

        tuim::SetCurrentCursor({2*(cursor.x - origin.x), cursor.y - origin.y});
        tuim::Print("#_ffffff  &r");

        for (auto& [id, city] : world->GetCities()) {
            if (city->GetPosition().x < origin.x
                || city->GetPosition().x > end.x
                || city->GetPosition().y < origin.y
                || city->GetPosition().y > end.y)
                continue;
            // Display the cursor over the city icon, but not the name.
            if (cursor != city->GetPosition()) {
                tuim::SetCurrentCursor({2*(city->GetPosition().x - origin.x), city->GetPosition().y - origin.y});
                tuim::Print("#_666666🏘 &r");
            }
            if (city->GetPosition().y > origin.y) {
                int x = 2*(city->GetPosition().x - origin.x) - (int)(tuim::CalcTextWidth(city->GetName())/2)+1;
                std::string cityName = (x < 0 ? city->GetName().substr(-x) : city->GetName());
                tuim::SetCurrentCursor({std::max(0, x), city->GetPosition().y - 1 - origin.y});
                tuim::Print("#_ffffff#000000{}&r", cityName);
            }
        }

        tuim::SetCurrentCursor({0, mapSize.y-3});
        tuim::Print("#_666666Press M to open map&r");
        
        std::string coordsText = fmt::format("#_666666({}, {})&r", state->GetCursor().x, state->GetCursor().y);
        tuim::SetCurrentCursor({mapSize.x - (int) tuim::CalcTextWidth(coordsText)+3, mapSize.y-3});
        tuim::Print(coordsText);
    }
    tuim::EndContainer();

    // Store data that are going to be neccessary for the sidebar.
    City* tileCity = world->GetCity(cursor);
    Building* tileBuilding = world->GetBuilding(cursor);

    std::string tileTitle = (
        tileCity != nullptr ? tileCity->GetName() :
        tileBuilding  != nullptr ? tileBuilding->GetType()->GetName() :
        "Empty Tile"
    );
    std::string tileType = (
        tileCity != nullptr ? "City" :
        tileBuilding  != nullptr ? BuildingTypesLabels[(int) tileBuilding->GetType()->GetType()] :
        ""
    );

    int titleHeight = 4;
    int sidebarWidth = terminalSize.x - mapSize.x;
    tuim::SetCurrentCursor({0, UI::HEADER_HEIGHT-1});
    tuim::BeginContainer("#container-title", "", {sidebarWidth+1, titleHeight}, tuim::CONTAINER_FLAGS_NONE, tuim::ALIGN_CENTER);
    tuim::BeginContainer("#container-title-inner", "", {(int) tuim::CalcTextWidth(tileTitle), 2}, tuim::CONTAINER_FLAGS_BORDERLESS);
    tuim::Print("&b{}&r\n", tileTitle);
    tuim::EndContainer();
    tuim::BeginContainer("#container-type-inner", "", {(int) tuim::CalcTextWidth(tileType), 1}, tuim::CONTAINER_FLAGS_BORDERLESS);
    tuim::Print("#666666{}&r", tileType);
    tuim::EndContainer();
    tuim::EndContainer();

    tuim::SetCurrentCursor({0, UI::HEADER_HEIGHT+titleHeight-2});
    tuim::BeginContainer("#container-sidebar", "", {sidebarWidth+1, terminalSize.y-UI::HEADER_HEIGHT-titleHeight+2});
    
    
    static bool showTileInfo = true;
    static bool showProduction = false;
    static bool showActions = false;
    static bool showStockpile = false;

    if (tuim::HomeMenuButton("#button-show-info", "&bInformation&r")) showTileInfo = !showTileInfo;
    if (showTileInfo) {
        tuim::Print("\n\n");

        tuim::SetCurrentCursor({2, tuim::GetCurrentCursor().y});
        tuim::BeginContainer("#container-sidebar-info", "", {sidebarWidth-3, 10}, tuim::CONTAINER_FLAGS_BORDERLESS);

        if (tileCity != nullptr) {
            tuim::Print("Name: {}\n", tileTitle);
            tuim::Print("Type: {}\n", tileType);
            tuim::Print("Population: {:L}\n", tileCity->GetPopulation());
        }
        else if (tileBuilding != nullptr) {
            tuim::Print("Owner: {}\n\n", "Cartel X");
            tuim::Print("Name: {}\n", tileTitle);
            tuim::Print("Type: {}\n", tileType);
            tuim::Print("Level: {}\n", 1);
            tuim::Print("Value: ${:L}\n", 1*tileBuilding->GetType()->GetPrice());
            tuim::Print("Employees: {:L}/{:L}\n", 0, tileBuilding->GetType()->GetEmployees());
            tuim::Print("Productivity: #aa0000{}%&r\n", 0);
        }
        tuim::EndContainer();
    }
    tuim::Print("\n");

    if (tileBuilding != nullptr && tileBuilding->GetType()->GetType() == BuildingTypes::PRODUCTION) {
        if (tuim::HomeMenuButton("#button-show-production", "&bProduction&r")) showProduction = !showProduction;
        if (showProduction) {
            tuim::Print("\n\n");

            tuim::SetCurrentCursor({2, tuim::GetCurrentCursor().y});
            tuim::BeginContainer("#container-sidebar-production", "", {sidebarWidth-3, 10}, tuim::CONTAINER_FLAGS_BORDERLESS);

            ProductionChain* productionChain = tileBuilding->GetType()->GetProductionChain();
            for (auto& [input, quantity] : productionChain->GetInputs()) {
                tuim::Print("#aa0000{}x {}&r\n", quantity, input->GetName());
            }
            if (productionChain->GetInputs().empty()) tuim::Print("Nothing\n");
            tuim::Print("\t⇓\n");
            for (auto& [output, quantity] : productionChain->GetOutputs()) {
                tuim::Print("#aaaaaa{}x {}&r\n", quantity, output->GetName());
            }
            if (productionChain->GetOutputs().empty()) tuim::Print("Nothing\n");

            int remainingDays = ((productionChain->GetStart() + productionChain->GetDuration()) - world->GetDate());
            tuim::Print("\nTime Left: {} days\n", (remainingDays < 0 ? "N/A" : std::to_string(remainingDays)));

            tuim::EndContainer();
        }
        tuim::Print("\n");
    }
    
    if (tuim::HomeMenuButton("#button-show-stockpile", "&bStockpile&r")) showStockpile = !showStockpile;
    if (tileBuilding != nullptr && showStockpile) {
        tuim::Print("\n\n");

        tuim::SetCurrentCursor({2, tuim::GetCurrentCursor().y});
        tuim::BeginContainer("#container-sidebar-stockpile", "", {sidebarWidth-3, 10}, tuim::CONTAINER_FLAGS_BORDERLESS);

        Stockpile* stockpile = tileBuilding->GetStockpile();

        tuim::Print("\nVolume: {:.1f}/{:.1f} m^3\n", (stockpile->GetMaxVolume() - stockpile->GetVolume())/1000.f, stockpile->GetMaxVolume()/1000.f);

        for (auto& [id, item] : stockpile->GetItems()) {
            tuim::Print("\t{}x {}&r\n", item->GetQuantity(), item->GetType()->GetName());
        }

        tuim::EndContainer();
    }
    tuim::Print("\n");
    
    if (tuim::HomeMenuButton("#button-show-actions", "&bActions&r")) showActions = !showActions;
    if (showActions) {
        tuim::Print("\n\n");
        tuim::SetCurrentCursor({2, tuim::GetCurrentCursor().y});
        tuim::BeginContainer("#container-sidebar-actions", "", {sidebarWidth-3, 5}, tuim::CONTAINER_FLAGS_BORDERLESS);
        
        if (tileCity == nullptr && tileBuilding == nullptr) {
            static size_t buildingIndex = 0;
            std::vector<std::string> buildingTypes;
            for (auto& [id, _] : world->GetBuildingTypes()) buildingTypes.push_back(id);
            tuim::EnumInput("input-create-building", "Construct a < {} > building", &buildingIndex, buildingTypes);
            if (tuim::IsItemHovered() && tuim::IsKeyPressed(tuim::ENTER)) {
                BuildingType* type = world->GetBuildingTypes()[buildingTypes[buildingIndex]].get();
                world->AddBuilding(MakeUnique<Building>(
                    type,
                    state->GetCursor()
                ));
            }
            tuim::Print("\n");
        }
        else if (tileBuilding != nullptr) {
            if (tuim::HomeMenuButton("#button-destroy-building", fmt::format("Destroy {}", tileTitle)))
                world->RemoveBuilding(state->GetCursor());
            tuim::Print("\n");
        }

        tuim::EndContainer();
    }
    tuim::Print("\n");

    tuim::Print("\n");
    if (tuim::HomeMenuButton("#button-back", "&bBack&r"))
        m_State->PopMenu();
        
    tuim::EndContainer();
    
    tuim::EndContainer();
    tuim::Display();
}