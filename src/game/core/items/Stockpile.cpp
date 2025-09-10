#include "Stockpile.hpp"
#include "game/core/Includes.hpp"

Stockpile::Stockpile() : m_MaxVolume(0), m_Volume(0) {}

Stockpile::Stockpile(int maxVolume) : m_MaxVolume(maxVolume), m_Volume(0) {}

int Stockpile::GetVolume() const {
    return m_Volume;
}

int Stockpile::GetMaxVolume() const {
    return m_MaxVolume;
}

std::unordered_multimap<std::string, UniquePtr<ItemStack>>& Stockpile::GetItems() {
    return m_Items;
}

std::vector<ItemStack*> Stockpile::GetItems(const std::string& id) {
    std::vector<ItemStack*> items;
    auto range = m_Items.equal_range(id);
    for (auto it = range.first; it != range.second; it++)
        items.push_back(it->second.get());
    return items;
}

bool Stockpile::Contains(const std::string& id, int amount) {
    int quantity = 0;

    auto range = m_Items.equal_range(id);
    for (auto it = range.first; it != range.second; it++) {
        quantity += it->second->GetQuantity();
    }

    return quantity >= amount;
}

bool Stockpile::Contains(Item* type, int amount) {
    return this->Contains(type->GetId(), amount);
}

void Stockpile::AddItem(UniquePtr<ItemStack> item) {
    // Make sure there is enough space for this itemstack.
    if (m_Volume + item->GetVolume() > m_MaxVolume)
        return;
    
    // Update the cached stockpile volume.
    m_Volume += item->GetVolume();

    // Check if there isn't already a similar itemstack that we could
    // increment instead of adding another one.
    auto range = m_Items.equal_range(item->GetType()->GetId());
    for (auto it = range.first; it != range.second; it++) {
        if (it->second->GetQuality() != item->GetQuality())
            continue;
        it->second->SetQuantity(it->second->GetQuantity() + item->GetQuantity());
        return;
    }

    // Add the itemstack otherwise.
    m_Items.insert({item->GetType()->GetId(), std::move(item)});
}

void Stockpile::RemoveItem(UniquePtr<ItemStack> item) {
    // TODO: improve performances for this function.

    // Make sure there are enough items to remove.
    // if (!this->Contains(item->GetType()->GetId(), item->GetQuantity()));
    //     return;

    int quantityToRemove = item->GetQuantity();

    auto range = m_Items.equal_range(item->GetType()->GetId());
    for (auto it = range.first; it != range.second;) {
        int quantity = std::min((int) it->second->GetQuantity(), quantityToRemove);
        quantityToRemove -= quantity;
        it->second->SetQuantity(it->second->GetQuantity() - quantity);

        if (it->second->GetQuantity() <= 0) {
            it = m_Items.erase(it);
        }
        else {
            it++;
        }

        if (quantityToRemove == 0)
            break;
    }
    
    // Update the cached stockpile volume.
    m_Volume -= item->GetVolume();
}