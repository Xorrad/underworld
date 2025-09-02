#include "Item.hpp"

Item::Item(const std::string& id, const std::string& name, double weight, double volume, double basePrice) :
    m_Id(id),
    m_Name(name),
    m_Weight(weight),
    m_Volume(volume),
    m_BasePrice(basePrice)
{}

const std::string& Item::GetId() const {
    return m_Id;
}

const std::string& Item::GetName() const {
    return m_Name;
}

double Item::GetWeight() const {
    return m_Weight;
}

double Item::GetVolume() const {
    return m_Volume;
}

double Item::GetBasePrice() const {
    return m_BasePrice;
}