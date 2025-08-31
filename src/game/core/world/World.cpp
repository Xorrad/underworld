#include "World.hpp"
#include "game/states/InGameState.hpp"
#include "game/core/world/Scenario.hpp"
#include "game/core/world/State.hpp"
#include "game/core/world/Country.hpp"
#include "game/core/world/City.hpp"

World::World() {}

World::World(UniquePtr<Scenario> scenario) :
    m_Scenario(std::move(scenario)),
    m_States(),
    m_Countries(),
    m_Cities(),
    m_StatesImage(nullptr),
    m_TerrainImage(nullptr),
    m_Terrain(),
    m_Defines({}),
    m_Date(Date::Epoch())
{
    m_Scenario->Load(this);
}

std::mutex& World::GetMutex() {
    return m_Mutex;
}

Scenario* World::GetScenario() {
    return m_Scenario.get();
}

std::unordered_map<std::string, UniquePtr<State>>& World::GetStates() {
    return m_States;
}

std::unordered_map<std::string, UniquePtr<Country>>& World::GetCountries() {
    return m_Countries;
}

std::unordered_map<std::string, UniquePtr<City>>& World::GetCities() {
    return m_Cities;
}

Image* World::GetStatesImage() {
    return m_StatesImage.get();
}

Image* World::GetTerrainImage() {
    return m_TerrainImage.get();
}

std::vector<std::vector<std::string>>& World::GetTerrain() {
    return m_Terrain;
}

nlohmann::json World::GetDefines() const {
    return m_Defines;
}

nlohmann::json World::GetDefine(const std::string& name) const {
    return m_Defines[name];
}

Date World::GetDate() const {
    return m_Date;
}

void World::SetScenario(UniquePtr<Scenario> scenario) {
    m_Scenario = std::move(scenario);
}

void World::AddState(UniquePtr<State> state) {
    m_States[state->GetId()] = std::move(state);
}

void World::RemoveState(State* state) {
    m_States.erase(state->GetId());
}

void World::RemoveState(std::string id) {
    m_States.erase(id);
}

void World::AddCountry(UniquePtr<Country> country) {
    m_Countries[country->GetId()] = std::move(country);
}

void World::RemoveCountry(Country* country) {
    m_Countries.erase(country->GetId());
}

void World::RemoveCountry(std::string id) {
    m_Countries.erase(id);
}

void World::AddCity(UniquePtr<City> city) {
    m_Cities[city->GetId()] = std::move(city);
}

void World::RemoveCity(City* city) {
    m_Cities.erase(city->GetId());
}

void World::RemoveCity(std::string id) {
    m_Cities.erase(id);
}

void World::SetStatesImage(UniquePtr<Image> statesImage) {
    m_StatesImage = std::move(statesImage);
}

void World::SetTerrainImage(UniquePtr<Image> terrainImage) {
    m_TerrainImage = std::move(terrainImage);
}

void World::SetTerrain(std::vector<std::vector<std::string>> terrain) {
    m_Terrain = terrain;
}

void World::SetDefines(nlohmann::json defines) {
    m_Defines = defines;
}

void World::AddDefine(const std::string& name, nlohmann::json value) {
    m_Defines[name] = value;
}

void World::SetDate(Date date) {
    m_Date = date;
}

void World::Update(InGameState* state) {
    m_Date = m_Date + 1;
}