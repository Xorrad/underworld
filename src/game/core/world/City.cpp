#include "City.hpp"

City::City(std::string id, std::string name, int population, Vec2<int> position) :
    m_Id(id),
    m_Name(name),
    m_Population(population),
    m_Position(position)
{}

std::string City::GetId() const {
    return m_Id;
}

std::string City::GetName() const {
    return m_Name;
}

int City::GetPopulation() const {
    return m_Population;
}

Vec2<int> City::GetPosition() const {
    return m_Position;
}