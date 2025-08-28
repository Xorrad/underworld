#include "InGameState.hpp"
#include "game/Game.hpp"
#include "game/ui/menus/ingame/OverviewMenu.hpp"

InGameState::InGameState(Game* game) : State(game) {
    this->PushMenu(MakeUnique<UI::OverviewMenu>(game, this));
}