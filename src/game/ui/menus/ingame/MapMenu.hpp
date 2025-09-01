#pragma once

#include "game/ui/menus/IMenu.hpp"

namespace UI {

class MapMenu : public IMenu {
public:
    MapMenu(Game* game, IState* state);

    void Update(char32_t key, bool skipInput = false) override;
    void Render() override;
};

}