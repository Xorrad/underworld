#include <iostream>
#include <memory> // std::unique_ptr, std::shared_ptr...
#include <vector> // std::vector
#include <string> // std::string

#include "util/SignalHandler.hpp"
const SignalHandler SIGNAL_HANDLER;

class Game;

namespace Core {
    
}

namespace State {
    class GameState;
}

namespace UI {
    class UI;
    class Menu;
}

#include "util/Ptr.hpp"

#include "game/Game.hpp"