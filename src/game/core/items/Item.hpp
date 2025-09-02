#pragma once

class Item {
public:
    Item(const std::string& id, const std::string& name, double weight, double volume, double basePrice);

    const std::string& GetId() const;
    const std::string& GetName() const;
    double GetWeight() const;
    double GetVolume() const;
    double GetBasePrice() const;

private:
    std::string m_Id;
    std::string m_Name;
    double m_Weight;
    double m_Volume;
    double m_BasePrice;
};
