#include "IFaction.hpp"

IFaction::IFaction(const std::string& id, const std::string& name, bool isPlayer) :
    m_Id(id),
    m_Name(name),
    m_IsPlayer(isPlayer)
{}

std::string IFaction::GetId() const {
    return m_Id;
}

std::string IFaction::GetName() const {
    return m_Name;
}

void IFaction::SetName(const std::string& name) {
    m_Name = name;
}

bool IFaction::IsPlayer() const {
    return m_IsPlayer;
}