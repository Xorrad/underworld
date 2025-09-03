#pragma once

#include <nlohmann/json.hpp>

class World {
public:
    World();
    World(UniquePtr<Scenario> scenario);

    std::mutex& GetMutex();

    Scenario* GetScenario();
    std::unordered_map<std::string, UniquePtr<State>>& GetStates();
    std::unordered_map<std::string, UniquePtr<Country>>& GetCountries();
    std::unordered_map<std::string, UniquePtr<City>>& GetCities();
    City* GetCity(Vec2<int> position);
    std::unordered_map<std::string, UniquePtr<Item>>& GetItems();
    std::unordered_map<std::string, UniquePtr<BuildingType>>& GetBuildingTypes();
    
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
    
    void AddItem(UniquePtr<Item> item);

    void AddBuildingType(UniquePtr<BuildingType> buildingType);

    void SetStatesImage(UniquePtr<Image> statesImage);
    void SetTerrainImage(UniquePtr<Image> terrainImage);
    void SetTerrain(std::vector<std::vector<std::string>> terrain);

    void SetDefines(nlohmann::json defines);
    void AddDefine(const std::string& name, nlohmann::json value);
    void SetDate(Date date);

    void Update(InGameState* state);

private:
    std::mutex m_Mutex;

    UniquePtr<Scenario> m_Scenario;
    std::unordered_map<std::string, UniquePtr<State>> m_States;
    std::unordered_map<std::string, UniquePtr<Country>> m_Countries;
    std::unordered_map<std::string, UniquePtr<City>> m_Cities;
    std::unordered_map<Vec2<int>, City*> m_CitiesByPosition;

    std::unordered_map<std::string, UniquePtr<Item>> m_Items;
    std::unordered_map<std::string, UniquePtr<BuildingType>> m_BuildingTypes;

    UniquePtr<Image> m_StatesImage;
    UniquePtr<Image> m_TerrainImage;
    UniquePtr<Image> m_MinimapImage;
    std::vector<std::vector<std::string>> m_Terrain;

    nlohmann::json m_Defines;
    Date m_Date;
};