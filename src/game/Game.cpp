#include "Game.hpp"
#include "tuim/tuim.hpp"

Game::Game() {

}

void Game::Init(int argc, char* argv[]) {
    // Store the command line arguments.
    // TODO: add options like -debug, -test to speed up development.
    m_Args.reserve(argc);
    for (int i = 0; i < argc; i++)
        m_Args.push_back(argv[i]);

    // Initialize tuim.
    tuim::CreateContext(argc, argv);
    tuim::SetTitle("Underworld: Organized Crime");
    tuim::SetFramerate(1.f);
}

void Game::Run() {
    char32_t keyCode = 0;
    while (keyCode != tuim::Key::F1) {
        keyCode = tuim::PollKeyCode();
        tuim::Update(keyCode);
        tuim::Clear();

        tuim::Print("main\n");
        tuim::Print("{}", time(0));

        tuim::Display();
    }
}

void Game::Exit() {
    // Deinitialize tuim.
    tuim::DeleteContext();
}