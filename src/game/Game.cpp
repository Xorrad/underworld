#include "Game.hpp"
#include "game/states/HomeState.hpp"

Game::Game() :
    m_Args(std::vector<const char*>{}),
    m_State(MakeUnique<HomeState>(this)),
    m_IsRunning(true)
{}

IState* Game::GetState() {
    return m_State.get();
}

bool Game::IsRunning() const {
    return m_IsRunning;
}

void Game::SetRunning(bool running) {
    m_IsRunning = running;
}

void Game::SetState(UniquePtr<IState> state) {
    m_State = std::move(state);
}

void Game::Init(int argc, char* argv[]) {
    // Store the command line arguments.
    // TODO: add options like -debug, -test to speed up development.
    m_Args.reserve(argc);
    for (int i = 0; i < argc; i++)
        m_Args.push_back(argv[i]);

    Configuration::Initialize();

    // Initialize tuim.
    tuim::CreateContext(argc, argv);
    tuim::SetTitle("Underworld: Organized Crime");
    tuim::SetFramerate(1.f);
    tuim::DefineStyle('b', tuim::Style::BOLD);
    tuim::DefineStyle('d', tuim::Style::FAINT);
    tuim::DefineStyle('i', tuim::Style::ITALIC);
    tuim::DefineStyle('u', tuim::Style::UNDERLINE);
    tuim::DefineStyle('g', tuim::Style::BLINKING);
    tuim::DefineStyle('n', tuim::Style::REVERSE);
    tuim::DefineStyle('h', tuim::Style::HIDDEN);
    tuim::DefineStyle('s', tuim::Style::STRIKETHROUGH);
}

void Game::Run() {
    while (m_IsRunning) {
        m_State->Update();
        m_State->Render();
    }
}

void Game::Exit() {
    Configuration::Save();

    // Deinitialize tuim.
    tuim::DeleteContext();
}