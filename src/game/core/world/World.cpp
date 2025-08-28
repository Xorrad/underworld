#include "World.hpp"
#include "game/core/world/State.hpp"
#include "game/core/world/Country.hpp"
#include "game/core/world/City.hpp"

World::World() {}

std::unordered_map<std::string, UniquePtr<State>>& World::GetStates() {
    return m_States;
}

std::unordered_map<std::string, UniquePtr<Country>>& World::GetCountries() {
    return m_Countries;
}

std::unordered_map<std::string, UniquePtr<City>>& World::GetCities() {
    return m_Cities;
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