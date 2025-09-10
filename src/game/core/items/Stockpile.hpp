#pragma once

class Stockpile {
public:
    Stockpile();
    Stockpile(int maxVolume);

    int GetVolume() const;
    int GetMaxVolume() const;
    std::unordered_multimap<std::string, UniquePtr<ItemStack>>& GetItems();
    std::vector<ItemStack*> GetItems(const std::string& id);

    bool Contains(const std::string& id, int amount);
    bool Contains(Item* type, int amount);

    void AddItem(UniquePtr<ItemStack> item);
    void RemoveItem(UniquePtr<ItemStack> item);

private:
    int m_MaxVolume;
    int m_Volume; // Cached and updated when items are added or removed
    std::unordered_multimap<std::string, UniquePtr<ItemStack>> m_Items;
};