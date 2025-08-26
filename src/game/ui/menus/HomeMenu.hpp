#pragma once

#include "game/ui/menus/Menu.hpp"

namespace UI {

class HomeMenu : public Menu {
public:
    HomeMenu(Game* game, State* state);

    void Update() override;
    void Render() override;
};

}