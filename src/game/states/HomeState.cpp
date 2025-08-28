#include "HomeState.hpp"
#include "game/Game.hpp"
#include "game/ui/menus/home/HomeMenu.hpp"

HomeState::HomeState(Game* game) : State(game) {
    this->PushMenu(MakeUnique<UI::HomeMenu>(game, this));
}