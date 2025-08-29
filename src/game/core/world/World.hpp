#pragma once

class World {
public:
    World();
    World(UniquePtr<Scenario> scenario);

    Scenario* GetScenario();
    std::unordered_map<std::string, UniquePtr<State>>& GetStates();
    std::unordered_map<std::string, UniquePtr<Country>>& GetCountries();
    std::unordered_map<std::string, UniquePtr<City>>& GetCities();

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

private:
    UniquePtr<Scenario> m_Scenario;
    std::unordered_map<std::string, UniquePtr<State>> m_States;
    std::unordered_map<std::string, UniquePtr<Country>> m_Countries;
    std::unordered_map<std::string, UniquePtr<City>> m_Cities;
};