#pragma once

class Configuration {
public:
    Configuration() = delete;
    Configuration(const Configuration&) = delete;
    Configuration& operator=(const Configuration&) = delete;

    // Build Definitions
    inline static std::string buildVersion = "1.0.0";
    inline static std::string buildCredits = "made by Xorrad";
    inline static std::string githubURL = "https://github.com/Xorrad/underworld";
    
    // Saved Settings
    inline static std::string dataPath = "data";
    inline static std::string settingsFile = "settings.json";
    inline static bool debugMode = false;

    // Graphics
    inline static tuim::vec2 windowResolution = tuim::Terminal::GetTerminalSize();

    static void Initialize();
    static void Load();
    static void Save();

private:
};