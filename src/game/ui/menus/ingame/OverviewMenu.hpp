#pragma once

#include "game/ui/menus/IMenu.hpp"

namespace UI {

class OverviewMenu : public IMenu {
public:
    OverviewMenu(Game* game, IState* state);

    void Update(bool skipInput = false) override;
    void Render() override;
};

}