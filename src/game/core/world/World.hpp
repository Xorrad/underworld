#pragma once

#include <nlohmann/json.hpp>

class World {
public:
    World();
    World(UniquePtr<Scenario> scenario);

    Scenario* GetScenario();
    std::unordered_map<std::string, UniquePtr<State>>& GetStates();
    std::unordered_map<std::string, UniquePtr<Country>>& GetCountries();
    std::unordered_map<std::string, UniquePtr<City>>& GetCities();
    
    Image* GetStatesImage();
    Image* GetTerrainImage();
    std::vector<std::vector<std::string>>& GetTerrain();

    nlohmann::json GetDefines() const;
    nlohmann::json GetDefine(const std::string& name) const;
    Date GetDate() const;

    void SetScenario(UniquePtr<Scenario> scenario);

    void AddState(UniquePtr<State> state);
    void RemoveState(State* state);
    void RemoveState(std::string id);

    void AddCountry(UniquePtr<Country> country);
    void RemoveCountry(Country* country);
    void RemoveCountry(std::string id);
    
    void AddCity(UniquePtr<City> city);
    void RemoveCity(City* city);
    void RemoveCity(std::string id);

    void SetStatesImage(UniquePtr<Image> statesImage);
    void SetTerrainImage(UniquePtr<Image> terrainImage);
    void SetTerrain(std::vector<std::vector<std::string>> terrain);

    void SetDefines(nlohmann::json defines);
    void AddDefine(const std::string& name, nlohmann::json value);
    void SetDate(Date date);

private:
    UniquePtr<Scenario> m_Scenario;
    std::unordered_map<std::string, UniquePtr<State>> m_States;
    std::unordered_map<std::string, UniquePtr<Country>> m_Countries;
    std::unordered_map<std::string, UniquePtr<City>> m_Cities;

    UniquePtr<Image> m_StatesImage;
    UniquePtr<Image> m_TerrainImage;
    UniquePtr<Image> m_MinimapImage;
    std::vector<std::vector<std::string>> m_Terrain;

    nlohmann::json m_Defines;
    Date m_Date;
};