#pragma once

#include "game/ui/menus/IMenu.hpp"

namespace UI {

class SettingsMenu : public IMenu {
public:
    SettingsMenu(Game* game, IState* state);

    void Update(bool skipInput = false) override;
    void Render() override;
};

}