#include <iostream>
#include <memory> // std::unique_ptr, std::shared_ptr...
#include <vector> // std::vector
#include <string> // std::string
#include <tuim/tuim.hpp>

#include "util/SignalHandler.hpp"
const SignalHandler SIGNAL_HANDLER;

class Game;
class GameState;
class MainMenuState;

namespace UI {
    class UI;
    class Menu;
}

#include "util/Ptr.hpp"