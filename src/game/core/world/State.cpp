#include "State.hpp"

State::State(std::string id, std::string name, Color color, City* capital) :
    m_Id(id),
    m_Name(name),
    m_Color(color),
    m_Capital(capital)
{}

std::string State::GetId() const {
    return m_Id;
}

std::string State::GetName() const {
    return m_Name;
}

Color State::GetColor() const {
    return m_Color;
}

City* State::GetCapital() {
    return m_Capital;
}