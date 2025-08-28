#include <iostream>
#include <memory> // std::unique_ptr, std::shared_ptr...
#include <vector> // std::vector
#include <string> // std::string
#include <stack> // std::stack
#include <tuim/tuim.hpp>

#include "util/SignalHandler.hpp"
const SignalHandler SIGNAL_HANDLER;

class Game;
class State;
class HomeState;
class InGameState;
class Configuration;

namespace UI {
    class Menu;
    class HomeMenu;
    class SettingsMenu;
    class OverviewMenu;
}

#include "util/Ptr.hpp"
#include "game/core/Configuration.hpp"