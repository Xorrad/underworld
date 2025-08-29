#pragma once

class Scenario {
public:
    Scenario(std::string id, std::string name, std::string version, std::string dirPath);

    std::string GetId() const;
    std::string GetName() const;
    std::string GetVersion() const;
    std::string GetDirPath() const;

    static std::vector<UniquePtr<Scenario>> ListScenarios();
    void Load(World* world);

private:
    void LoadStates(World* world);
    void LoadCountries(World* world);
    void LoadCities(World* world);
    void LoadStatesImage(World* world);
    void LoadTerrainImage(World* world);

private:
    std::string m_Id;
    std::string m_Name;
    std::string m_Version;
    std::string m_DirPath;
};