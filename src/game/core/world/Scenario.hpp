#pragma once

class Scenario {
public:
    Scenario(std::string id, std::string name, std::string version, std::string dirPath);

    std::string GetId() const;
    std::string GetName() const;
    std::string GetVersion() const;
    std::string GetDirPath() const;

    static std::vector<UniquePtr<Scenario>> GetScenarios();
    static UniquePtr<World> Load(const std::string& scenario);

    static void LoadStates(const std::string& scenario, World* world);
    static void LoadCountries(const std::string& scenario, World* world);
    static void LoadCities(const std::string& scenario, World* world);
    static void LoadStatesImage(const std::string& scenario, World* world);
    static void LoadTerrainImage(const std::string& scenario, World* world);

private:
    std::string m_Id;
    std::string m_Name;
    std::string m_Version;
    std::string m_DirPath;
};