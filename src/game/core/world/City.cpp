#include "City.hpp"

City::City(std::string id, std::string name) :
    m_Id(id),
    m_Name(name)
{}

std::string City::GetId() const {
    return m_Id;
}

std::string City::GetName() const {
    return m_Name;
}