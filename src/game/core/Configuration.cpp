#include "Configuration.hpp"

#include <nlohmann/json.hpp>

void Configuration::Initialize() {
    windowResolution = tuim::Terminal::GetTerminalSize();

#ifdef DEBUG
    buildVersion = buildVersion + " (debug)";
    debugMode = true;
#endif

    Load();
}

void Configuration::Load() {
    // Import settings from the specified file as an json object.
    std::ifstream file(Configuration::dataPath + "/" + Configuration::settingsFile, std::ios::binary);
    if (!file) return;
    nlohmann::json data = nlohmann::json::parse(file);
    file.close();

    Configuration::debugMode = data.value("debugMode", false);
}

void Configuration::Save() {
    // Build a json object with all settings to save.
    nlohmann::json json;
    json["debugMode"] = Configuration::debugMode;

    // Dump that json object into the settings file.
    std::ofstream file(Configuration::dataPath + "/" + Configuration::settingsFile, std::ios::out);
    file << json.dump(1, '\t');
    file.close();
}