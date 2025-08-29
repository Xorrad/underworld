#include "Misc.hpp"
#include "game/states/InGameState.hpp"
#include "game/core/world/World.hpp"

void tuim::Minimap(const std::string& id, vec2 size, World* world) {
    tuim::BeginContainer(id, "", size);

    // The size is multiplied by 2 for the container because each pixel of
    // the minimap will be 2 character wide instead of one. This is to
    // compensate for the difference between characters width and height
    // in the terminal.
    size.x /= 2;

    ::Image* statesImage = world->GetStatesImage();
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

    tuim::EndContainer();
}