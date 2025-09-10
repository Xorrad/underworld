#include "ItemStack.hpp"
#include "Item.hpp"

ItemStack::ItemStack(Item* type, int quality, double quantity) :
    m_Type(type),
    m_Quality(quality),
    m_Quantity(quantity)
{}

Item* ItemStack::GetType() const {
    return m_Type;
}

int ItemStack::GetQuality() const {
    return m_Quality;
}

double ItemStack::GetQuantity() const {
    return m_Quantity;
}

int ItemStack::GetVolume() const {
    return m_Quantity * m_Type->GetVolume();
}

void ItemStack::SetType(Item* type) {
    m_Type = type;
}

void ItemStack::SetQuality(int quality) {
    m_Quality = quality;
}

void ItemStack::SetQuantity(double quantity) {
    m_Quantity = quantity;
}