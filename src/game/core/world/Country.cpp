#include "Country.hpp"

Country::Country(std::string id, std::string name, City* capital, std::vector<State*> states) :
    m_Id(id),
    m_Name(name),
    m_Capital(capital),
    m_States(states)
{}

std::string Country::GetId() const {
    return m_Id;
}

std::string Country::GetName() const {
    return m_Name;
}

City* Country::GetCapital() {
    return m_Capital;
}

std::vector<State*> Country::GetStates() {
    return m_States;
}