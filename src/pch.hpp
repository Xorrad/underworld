#include <iostream>
#include <memory> // std::unique_ptr, std::shared_ptr...
#include <vector> // std::vector
#include <string> // std::string
#include <stack> // std::stack
#include <cmath> // std::fmod, std::round...
#include <charconv> // std::from_chars
#include <unordered_map> // std::unordered_map
#include <tuim/tuim.hpp>

#include "util/SignalHandler.hpp"
const SignalHandler SIGNAL_HANDLER;

class Game;
class IState;
class HomeState;
class InGameState;
class Configuration;

class World;
class Country;
class State;
class City;

namespace UI {
    class IMenu;
    class HomeMenu;
    class SettingsMenu;
    class OverviewMenu;
}

#include "util/Ptr.hpp"
#include "util/Color.hpp"
#include "game/core/Configuration.hpp"