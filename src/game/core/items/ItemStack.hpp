#pragma once

class ItemStack {
public:
    ItemStack(Item* type, int quality, double quantity);

    Item* GetType() const;
    int GetQuality() const;
    double GetQuantity() const;
    int GetVolume() const;

    void SetType(Item* type);
    void SetQuality(int quality);
    void SetQuantity(double quantity);
    
private:
    Item* m_Type;
    int m_Quality;
    double m_Quantity;
};