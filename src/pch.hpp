#include <iostream>
#include <memory> // std::unique_ptr, std::shared_ptr...
#include <vector> // std::vector
#include <string> // std::string
#include <stack> // std::stack
#include <cmath> // std::fmod, std::round...
#include <charconv> // std::from_chars
#include <unordered_map> // std::unordered_map
#include <set> // std::set
#include <sstream> // std::getline
#include <thread> // std::thread, std::this_thread
#include <mutex> // std::lock_guard, std::unique_lock
#include <atomic> // std::atomic
#include <condition_variable> // std::condition_variable
#include <chrono> // std::chrono
#include <tuim/tuim.hpp>

#include "util/SignalHandler.hpp"
const SignalHandler SIGNAL_HANDLER;

class Game;
class IState;
class HomeState;
class InGameState;
class Configuration;
class Image;
class Date;

class Scenario;
class World;
class Country;
class State;
class City;
class Item;
class ItemStack;
class ProductionChain;
class BuildingType;
class Building;

namespace UI {
    class IMenu;
    class HomeMenu;
    class SettingsMenu;
    class OverviewMenu;
    class MapMenu;
}

#include "util/Ptr.hpp"
#include "util/Vec2.hpp"
#include "util/File.hpp"
#include "util/Color.hpp"
#include "util/Image.hpp"
#include "util/Date.hpp"
#include "game/core/Configuration.hpp"
#include "game/ui/Defines.hpp"
#include "game/core/buildings/BuildingTypes.hpp"