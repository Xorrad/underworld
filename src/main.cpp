#include "game/Game.hpp"

int main(int argc, char* argv[]) {
    Game game;
    game.Init(argc, argv);
    game.Run();
    game.Exit();
    return 0;
}