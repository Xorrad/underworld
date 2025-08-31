#pragma once

#include "game/states/IState.hpp"

class InGameState : public IState {
public:
    InGameState(Game* game, UniquePtr<World> world);
    ~InGameState();

    bool IsExitingToHomeMenu() const;
    World* GetWorld();
    int GetGameSpeed() const;
    bool IsPaused() const;
    Vec2<int> GetCursor() const;

    void SetExitToHomeMenu(bool exit);
    void SetCursor(Vec2<int> cursor);

    // This function is ran in a separate thread until m_Game->IsRunning() is false.
    // It updates the world such as characters, buildings, events...
    // The thread speed is defined by m_GameSpeed, ranging from 0 (paused) to 4.
    void UpdateWorld();

    void Update() override;
    void Render() override;

private:
    std::thread m_WorldThread;
    std::mutex m_WorldThreadCVMutex;
    std::condition_variable m_WorldThreadCV;

    std::atomic<bool> m_ExitToHomeMenu;

    UniquePtr<World> m_World;
    std::atomic<int> m_GameSpeed;
    std::atomic<bool> m_Paused;
    Vec2<int> m_Cursor;
};