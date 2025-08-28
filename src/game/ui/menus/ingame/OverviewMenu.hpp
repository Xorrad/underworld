#pragma once

#include "game/ui/menus/Menu.hpp"

namespace UI {

class OverviewMenu : public Menu {
public:
    OverviewMenu(Game* game, State* state);

    void Update(bool skipInput = false) override;
    void Render() override;
};

}