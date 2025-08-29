#include "InGameState.hpp"
#include "game/Game.hpp"
#include "game/core/world/World.hpp"
#include "game/core/world/Scenario.hpp"
#include "game/core/world/Country.hpp"
#include "game/core/world/State.hpp"
#include "game/core/world/City.hpp"
#include "game/ui/menus/ingame/OverviewMenu.hpp"

InGameState::InGameState(Game* game, UniquePtr<World> world) :
    IState(game),
    m_World(std::move(world))
{
    this->PushMenu(MakeUnique<UI::OverviewMenu>(game, this));
}

World* InGameState::GetWorld() {
    return m_World.get();
}