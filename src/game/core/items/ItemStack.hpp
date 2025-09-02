#pragma once

#include <string>

class ItemStack {
public:
    ItemStack(const std::string& itemId, int quality, double quantity);

    const std::string& getItemId() const;
    int getQuality() const;
    double getQuantity() const;

    void SetItemId(const std::string& itemId);
    void SetQuality(int quality);
    void SetQuantity(double quantity);
    
private:
    std::string m_ItemId;
    int m_Quality;
    double m_Quantity;
};