#include "Scenario.hpp"
#include "game/core/world/World.hpp"
#include "game/core/world/State.hpp"
#include "game/core/world/Country.hpp"
#include "game/core/world/City.hpp"

#include <nlohmann/json.hpp>
#include <lodepng/lodepng.h>
#include <fmt/format.h>

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

std::vector<UniquePtr<Scenario>> Scenario::ListScenarios() {
    std::vector<UniquePtr<Scenario>> scenarios;

    std::set<std::string> dirs = File::ListFiles(Configuration::dataPath + "/scenarios/", false);

    for (auto& dir : dirs) {
        if (!std::filesystem::is_directory(dir))
            continue;

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

void Scenario::Load(World* world) {
    try {
        this->LoadDefines(world);
        this->LoadItems(world);
        this->LoadCities(world);
        this->LoadStates(world);
        this->LoadCountries(world);
        this->LoadStatesImage(world);
        this->LoadTerrainImage(world);
    }
    catch (std::exception& e) {
        tuim::DeleteContext();
        std::cerr << e.what() << std::endl;
        exit(0);
    }
}

void Scenario::LoadDefines(World* world) {
    // Parse the defines file.
    std::string filePath = m_DirPath + "/defines/defines.json";
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return;
    nlohmann::json data = nlohmann::json::parse(file);
    
    // Initialize value depending on a define.
    world->SetDate(Date::FromString(data["startDate"]));

    // Store all defines to allow accessing them anytime.
    world->SetDefines(std::move(data));
}

void Scenario::LoadItems(World* world) {
    std::string filePath = m_DirPath + "/items/items.json";
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return;
    
    nlohmann::json data = nlohmann::json::parse(file);
    for(auto itemData : data) {
        UniquePtr<Item> city = MakeUnique<Item>(
            itemData["id"],
            itemData["name"],
            itemData["weight"],
            itemData["volume"],
            itemData["base_price"]
        );
        world->AddItem(std::move(city));
    }

    file.close();
}

void Scenario::LoadCities(World* world) {
    std::string filePath = m_DirPath + "/map/cities.json";
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return;
    
    nlohmann::json data = nlohmann::json::parse(file);
    for(auto cityData : data) {
        UniquePtr<City> city = MakeUnique<City>(
            cityData["id"],
            cityData["name"],
            cityData["population"],
            Vec2<int>{ cityData["position"][0], cityData["position"][1] }
        );
        world->AddCity(std::move(city));
    }

    file.close();
}

void Scenario::LoadStates(World* world) {
    std::string filePath = m_DirPath + "/map/states.json";
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return;
    
    nlohmann::json data = nlohmann::json::parse(file);
    for(auto stateData : data) {
        City* capital = nullptr;
        if (!stateData.value("capital", "").empty()) {
            auto it = world->GetCities().find(stateData["capital"]);
            if (it == world->GetCities().end()) {
                throw std::runtime_error(fmt::format("Unknown capital '{}' for state '{}'", stateData["capital"].get<std::string>(), stateData["id"].get<std::string>()));
            }
            else {
                capital = it->second.get();
            }
        }

        UniquePtr<State> state = MakeUnique<State>(
            stateData["id"],
            stateData["name"],
            Color::FromHex(stateData["color"].get<std::string>()),
            capital
        );
        world->AddState(std::move(state));
    }

    file.close();
}

void Scenario::LoadCountries(World* world) {
    std::string filePath = m_DirPath + "/map/countries.json";
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return;
    
    nlohmann::json data = nlohmann::json::parse(file);
    for(auto countryData : data) {
        // Make a list of all the country states.
        std::vector<State*> states;
        for (auto stateId : countryData["states"])
            states.push_back(world->GetStates().at(stateId).get());

        City* capital = nullptr;
        if (!countryData.value("capital", "").empty()) {
            auto it = world->GetCities().find(countryData["capital"]);
            if (it == world->GetCities().end()) {
                throw std::runtime_error(fmt::format("Unknown capital '{}' for country '{}'", countryData["capital"].get<std::string>(), countryData["id"].get<std::string>()));
            }
            else {
                capital = it->second.get();
            }
        }

        UniquePtr<Country> country = MakeUnique<Country>(
            countryData["id"],
            countryData["name"],
            capital,
            states
        );
        world->AddCountry(std::move(country));
    }

    file.close();
}

void Scenario::LoadStatesImage(World* world) {
    Image image = Image::LoadFromFile(m_DirPath + "/map/states.png");
    world->SetStatesImage(MakeUnique<Image>(image.GetWidth(), image.GetHeight(), std::move(image.GetPixels())));
}

void Scenario::LoadTerrainImage(World* world) {
    // Load the terrain coloring image.
    Image image = Image::LoadFromFile(m_DirPath + "/map/terrain.png");
    world->SetTerrainImage(MakeUnique<Image>(image.GetWidth(), image.GetHeight(), std::move(image.GetPixels())));

    // Ignore ascii terrain for now since the map looks way better
    // with colored terrain and no character.
    
    // Load the ascii terrain file.
    // std::string filePath = m_DirPath + "/map/terrain.txt";
    // std::ifstream file(filePath, std::ios::binary);
    // if (!file) return;
    // std::vector<std::vector<std::string>> lines;
    // std::string line;
    // while (std::getline(file, line)) {
    //     std::vector<std::string> characters;

    //     for (int i = 0; i < line.size();) {
    //         int charLength = tuim::Utf8CharLength(line[i]);
    //         characters.push_back(line.substr(i, charLength));
    //         i += charLength;
    //     }

    //     lines.push_back(characters);
    // }
    // world->SetTerrain(lines);
}