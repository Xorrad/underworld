#pragma once

namespace Scenario {
    UniquePtr<World> Load(const std::string& scenario);

    void LoadStates(const std::string& scenario, World* world);
    void LoadCountries(const std::string& scenario, World* world);
    void LoadCities(const std::string& scenario, World* world);
    void LoadStatesImage(const std::string& scenario, World* world);
    void LoadTerrainImage(const std::string& scenario, World* world);
}