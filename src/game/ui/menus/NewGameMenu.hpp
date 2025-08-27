#pragma once

#include "game/ui/menus/Menu.hpp"

namespace UI {

class NewGameMenu : public Menu {
public:
    NewGameMenu(Game* game, State* state);

    void Update(bool skipInput = false) override;
    void Render() override;
};

}