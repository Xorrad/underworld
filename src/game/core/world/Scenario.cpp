#include "Scenario.hpp"
#include "game/core/world/World.hpp"
#include "game/core/world/State.hpp"
#include "game/core/world/Country.hpp"
#include "game/core/world/City.hpp"

#include <nlohmann/json.hpp>

Scenario::Scenario(std::string id, std::string name, std::string version, std::string dirPath) :
    m_Id(id),
    m_Name(name),
    m_Version(version),
    m_DirPath(dirPath)
{}

std::string Scenario::GetId() const {
    return m_Id;
}

std::string Scenario::GetName() const {
    return m_Name;
}

std::string Scenario::GetVersion() const {
    return m_Version;
}

std::string Scenario::GetDirPath() const {
    return m_DirPath;
}

std::vector<UniquePtr<Scenario>> Scenario::GetScenarios() {
    std::vector<UniquePtr<Scenario>> scenarios;

    std::set<std::string> dirs = File::ListFiles(Configuration::dataPath + "/scenarios/", false);

    for (auto& dir : dirs) {
        if (!std::filesystem::is_directory(dir))
            continue;
        std::cout << dir << std::endl;

        std::ifstream descFile(dir + "/description.json", std::ios::binary);
        if (!descFile)
            continue;

        nlohmann::json data = nlohmann::json::parse(descFile);
        std::string id = data["id"];
        std::string name = data["name"];
        std::string version = data["version"];
        scenarios.push_back(MakeUnique<Scenario>(id, name, version, dir));
        descFile.close();
    }

    return scenarios;
}

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