#include "Building.hpp"
#include "game/core/Includes.hpp"

Building::Building(BuildingType* type, const Vec2<int>& position) :
    m_Type(type),
    m_Position(position),
    m_Stockpile(MakeUnique<Stockpile>(type->GetMaxVolume())),
    m_ProductionStartDate(Date::EPOCH)
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

Date Building::GetProductionStartDate() const {
    return m_ProductionStartDate;
}

Date Building::GetProductionEndDate() const {
    return m_ProductionStartDate + (24*m_Type->GetProductionChain()->GetDuration());
}

void Building::SetType(BuildingType* type) {
    m_Type = type;
}

void Building::SetPosition(const Vec2<int>& position) {
    m_Position = position;
}

void Building::SetProductionStartDate(const Date& date) {
    m_ProductionStartDate = date;
}