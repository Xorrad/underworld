#pragma once

#include "game/ui/menus/IMenu.hpp"

namespace UI {

class HomeMenu : public IMenu {
public:
    HomeMenu(Game* game, IState* state);

    void Update(bool skipInput = false) override;
    void Render() override;
};

}