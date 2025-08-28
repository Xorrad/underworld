#include "HomeState.hpp"
#include "game/Game.hpp"
#include "game/ui/menus/home/HomeMenu.hpp"

HomeState::HomeState(Game* game) : IState(game) {
    this->PushMenu(MakeUnique<UI::HomeMenu>(game, this));
}