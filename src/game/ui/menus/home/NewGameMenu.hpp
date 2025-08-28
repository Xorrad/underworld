#pragma once

#include "game/ui/menus/IMenu.hpp"

namespace UI {

class NewGameMenu : public IMenu {
public:
    NewGameMenu(Game* game, IState* state);

    void Update(bool skipInput = false) override;
    void Render() override;
};

}