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
    m_World(std::move(world)),
    m_GameSpeed(0),
    m_Cursor({(int) m_World->GetStatesImage()->GetWidth()/2, (int) m_World->GetStatesImage()->GetHeight()/2})
{
    this->PushMenu(MakeUnique<UI::OverviewMenu>(game, this));
}

World* InGameState::GetWorld() {
    return m_World.get();
}

int InGameState::GetGameSpeed() const {
    return m_GameSpeed;
}

Vec2<int> InGameState::GetCursor() const {
    return m_Cursor;
}

void InGameState::SetCursor(Vec2<int> cursor) {
    m_Cursor = cursor;   
}

void InGameState::Update() {
    m_World->SetDate(m_World->GetDate() + (1 * m_GameSpeed*m_GameSpeed));

    if (m_Menus.empty())
        return;
    m_Menus.top()->Update(m_FirstFrame);

    if (tuim::GetCtx()->m_ActiveItemId == 0) {
        if (tuim::IsKeyPressed(tuim::SPACE)) m_GameSpeed = 0;
        else if (tuim::IsKeyPressed(tuim::DIGIT_1)) m_GameSpeed = 1;
        else if (tuim::IsKeyPressed(tuim::DIGIT_2)) m_GameSpeed = 2;
        else if (tuim::IsKeyPressed(tuim::DIGIT_3)) m_GameSpeed = 3;
        else if (tuim::IsKeyPressed(tuim::DIGIT_4)) m_GameSpeed = 4;
    }
}