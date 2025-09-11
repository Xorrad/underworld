#include "Building.hpp"
#include "game/core/Includes.hpp"

Building::Building(BuildingType* type, const Vec2<int>& position) :
    m_Type(type),
    m_Position(position),
    m_Stockpile(MakeUnique<Stockpile>(type->GetMaxVolume()))
{}

BuildingType* Building::GetType() const {
    return m_Type;
}

const Vec2<int>& Building::GetPosition() const {
    return m_Position;
}

Stockpile* Building::GetStockpile() {
    return m_Stockpile.get();
}

void Building::SetType(BuildingType* type) {
    m_Type = type;
}

void Building::SetPosition(const Vec2<int>& position) {
    m_Position = position;
}
