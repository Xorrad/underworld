#include "Scenario.hpp"
#include "game/core/world/World.hpp"
#include "game/core/world/State.hpp"
#include "game/core/world/Country.hpp"
#include "game/core/world/City.hpp"

#include <nlohmann/json.hpp>

UniquePtr<World> Scenario::Load(const std::string& scenario) {
    UniquePtr<World> world = MakeUnique<World>();

    Scenario::LoadStates(scenario, world.get());
    Scenario::LoadCountries(scenario, world.get());
    Scenario::LoadCities(scenario, world.get());
    Scenario::LoadStatesImage(scenario, world.get());
    Scenario::LoadTerrainImage(scenario, world.get());

    return world;
}

void Scenario::LoadStates(const std::string& scenario, World* world) {
    std::string filePath = Configuration::dataPath + "/scenarios/" + scenario + "/map/states.json";
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return;
    
    nlohmann::json data = nlohmann::json::parse(file);
    for(auto stateData : data) {
        UniquePtr<State> state = MakeUnique<State>(
            stateData["id"],
            stateData["name"],
            Color::FromHex(stateData["color"].get<std::string>()),
            nullptr
        );
        world->AddState(std::move(state));
    }

    file.close();
}

void Scenario::LoadCountries(const std::string& scenario, World* world) {
    std::string filePath = Configuration::dataPath + "/scenarios/" + scenario + "/map/countries.json";
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return;
    
    nlohmann::json data = nlohmann::json::parse(file);
    for(auto countryData : data) {
        std::vector<State*> states;

        for (auto stateId : countryData["states"])
            states.push_back(world->GetStates().at(stateId).get());

        UniquePtr<Country> country = MakeUnique<Country>(
            countryData["id"],
            countryData["name"],
            nullptr,
            states
        );
        world->AddCountry(std::move(country));
    }

    file.close();
}

void Scenario::LoadCities(const std::string& scenario, World* world) {

}

void Scenario::LoadStatesImage(const std::string& scenario, World* world) {

}

void Scenario::LoadTerrainImage(const std::string& scenario, World* world) {

}