#include "InGameState.hpp"
#include "game/Game.hpp"
#include "game/core/world/World.hpp"
#include "game/core/world/Scenario.hpp"
#include "game/core/world/Country.hpp"
#include "game/core/world/State.hpp"
#include "game/core/world/City.hpp"
#include "game/states/HomeState.hpp"
#include "game/ui/menus/ingame/OverviewMenu.hpp"

InGameState::InGameState(Game* game, UniquePtr<World> world) :
    IState(game),
    m_ExitToHomeMenu(false),
    m_World(std::move(world)),
    m_GameSpeed(1),
    m_Paused(true),
    m_Cursor({(int) m_World->GetStatesImage()->GetWidth()/2, (int) m_World->GetStatesImage()->GetHeight()/2})
{
    this->PushMenu(MakeUnique<UI::OverviewMenu>(game, this));
    m_WorldThread  = std::thread(&InGameState::UpdateWorld, this);
}

InGameState::~InGameState() {
    if (m_WorldThread.joinable()) {
        m_ExitToHomeMenu = true;
        m_WorldThreadCV.notify_all();
        m_WorldThread.join();
    }
}

bool InGameState::IsExitingToHomeMenu() const {
    return m_ExitToHomeMenu;
}

World* InGameState::GetWorld() {
    return m_World.get();
}

int InGameState::GetGameSpeed() const {
    return m_GameSpeed;
}

bool InGameState::IsPaused() const {
    return m_Paused;
}

Vec2<int> InGameState::GetCursor() const {
    return m_Cursor;
}

void InGameState::SetExitToHomeMenu(bool exit) {
    m_ExitToHomeMenu = exit;
}

void InGameState::SetCursor(Vec2<int> cursor) {
    m_Cursor = cursor;   
}

void InGameState::UpdateWorld() {
    while(m_Game->IsRunning()) {
        {
            std::unique_lock<std::mutex> lock(m_WorldThreadCVMutex);
            m_WorldThreadCV.wait(lock, [&] { return !m_Paused || m_ExitToHomeMenu; });
        }

        if (m_ExitToHomeMenu)
            break;

        {
            std::lock_guard<std::mutex> lock(m_World->GetMutex());
            m_World->Update(this);
        }

        int millis = 1000 / std::max(1, m_GameSpeed*m_GameSpeed*m_GameSpeed);
        std::this_thread::sleep_for(std::chrono::milliseconds(millis));
    }
}

void InGameState::Update() {
    if (m_Menus.empty())
        return;

    char32_t key = (m_FirstFrame ? 0 : tuim::PollKeyCode());
    {
        std::lock_guard<std::mutex> lock(m_World->GetMutex());
        m_Menus.top()->Update(key, m_FirstFrame);

        if (tuim::GetCtx()->m_ActiveItemId == 0) {
            if (tuim::IsKeyPressed(tuim::SPACE)) m_Paused = !m_Paused;
            else if (tuim::IsKeyPressed(tuim::DIGIT_1)) { m_Paused = false; m_GameSpeed = 1; }
            else if (tuim::IsKeyPressed(tuim::DIGIT_2)) { m_Paused = false; m_GameSpeed = 2; }
            else if (tuim::IsKeyPressed(tuim::DIGIT_3)) { m_Paused = false; m_GameSpeed = 3; }
            else if (tuim::IsKeyPressed(tuim::DIGIT_4)) { m_Paused = false; m_GameSpeed = 4; }
            else if (tuim::IsKeyPressed(tuim::DIGIT_5)) { m_Paused = false; m_GameSpeed = 5; }
            m_WorldThreadCV.notify_all();
        }
    }
}

void InGameState::Render() {

    if (m_Menus.empty())
        return;
    
    // The first frame need to be rendered and then updated in order for
    // tuim to map out the items in the frame and which are hovered.
    if (m_FirstFrame) {
        {
            std::lock_guard<std::mutex> lock(m_World->GetMutex());
            m_Menus.top()->Render();
        }
        this->Update();
    }
    m_FirstFrame = false;

    {
        std::lock_guard<std::mutex> lock(m_World->GetMutex());
        m_Menus.top()->Render();
    }

    // If the game is closing, wait for the world thread to finish its update.
    if ((!m_Game->IsRunning() || m_ExitToHomeMenu) && m_WorldThread.joinable()) {
        m_WorldThreadCV.notify_all();
        m_WorldThread.join();
    }

    if (m_ExitToHomeMenu) {
        m_Game->SetState(MakeUnique<HomeState>(m_Game));
    }
}