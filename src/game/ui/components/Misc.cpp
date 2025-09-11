#include "Misc.hpp"
#include "game/states/InGameState.hpp"
#include "game/core/world/World.hpp"
#include "game/core/world/World.hpp"

void tuim::Header(InGameState* state) {
    tuim::vec2 terminalSize = tuim::Terminal::GetTerminalSize();

    tuim::BeginContainer("#container-header", "", {terminalSize.x, UI::HEADER_HEIGHT});
    tuim::Print("\n");
    tuim::SetCurrentCursor({1,  1}); tuim::Print("Your Organization Name");
    tuim::SetCurrentCursor({1,  2}); tuim::Print("Money: $2.5M / $11.2M");
    tuim::SetCurrentCursor({30, 2}); tuim::Print("Members: 52");
    tuim::SetCurrentCursor({50, 2}); tuim::Print("Territories: 5");

    if (state->IsPaused()) {
        tuim::SetCurrentCursor({terminalSize.x-2-7, 1}); tuim::Print("PAUSED");
    }
    else {
        int gameSpeed = state->GetGameSpeed();
        tuim::SetCurrentCursor({terminalSize.x-2-16, 1}); tuim::Print("Speed #555555");
        for (int i = 0; i < gameSpeed; i++)
            tuim::Print("█ ");
        tuim::Print("&r");
        for (int i = gameSpeed; i < 5; i++)
            tuim::Print("█ ");
    }

    std::string date = static_cast<InGameState*>(state)->GetWorld()->GetDate().ToStringFormatted();
    tuim::SetCurrentCursor({terminalSize.x-3-(int) tuim::CalcTextWidth(date), 2}); tuim::Print(date);
    tuim::EndContainer();
}

void tuim::Minimap(const std::string& id, vec2 size, World* world) {
    tuim::BeginContainer(id, "", size);

    // The size is multiplied by 2 for the container because each pixel of
    // the minimap will be 2 character wide instead of one. This is to
    // compensate for the difference between characters width and height
    // in the terminal.
    size.x /= 2;

    ::Image* statesImage = world->GetTerrainImage();
    // ::Image* statesImage = world->GetStatesImage();
    vec2 originalSize = vec2(statesImage->GetWidth(), statesImage->GetHeight());
    auto& pixels = statesImage->GetPixels();

    ::Color previousColor = ::Color(0, 0, 0, 0);

    for (uint32_t y = 0; y < size.y; y++) {
        for (uint32_t x = 0; x < size.x; x++) {
            uint32_t oldX = x * originalSize.x / size.x;
            uint32_t oldY = y * originalSize.y / size.y;
            uint32_t oldIndex = oldY * originalSize.x + oldX;
            if (previousColor != pixels[oldIndex]) {
                previousColor = pixels[oldIndex];
                tuim::Print("#_" + previousColor.ToHex());
            }
            tuim::Print("  ");
        }
        tuim::Print("\n");
    }
    tuim::Print("&r");

    tuim::SetCurrentCursor(vec2(0, size.y-3));
    tuim::Print("#_666666Press M to open map&r");
    tuim::EndContainer();
}