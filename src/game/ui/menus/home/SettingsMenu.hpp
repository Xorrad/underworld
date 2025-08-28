#pragma once

#include "game/ui/menus/Menu.hpp"

namespace UI {

class SettingsMenu : public Menu {
public:
    SettingsMenu(Game* game, State* state);

    void Update(bool skipInput = false) override;
    void Render() override;
};

}