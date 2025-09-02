#include "ItemStack.hpp"

ItemStack::ItemStack(const std::string& itemId, int quality, double quantity) :
    m_ItemId(itemId),
    m_Quality(quality),
    m_Quantity(quantity)
{}

const std::string& ItemStack::GetItemId() const {
    return m_ItemId;
}

int ItemStack::GetQuality() const {
    return m_Quality;
}

double ItemStack::GetQuantity() const {
    return m_Quantity;
}

void ItemStack::SetItemId(const std::string& itemId) {
    m_ItemId = itemId;
}

void ItemStack::SetQuality(int quality) {
    m_Quality = quality;
}

void ItemStack::SetQuantity(double quantity) {
    m_Quantity = quantity;
}