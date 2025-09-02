#pragma once

class Item {
public:
    Item(const std::string& id, const std::string& name, double weight, double volume, double basePrice)
        : m_Id(id), m_Name(name), m_Weight(weight), m_Volume(volume), m_BasePrice(basePrice) {}

    const std::string& GetId() const { return m_Id; }
    const std::string& GetName() const { return m_Name; }
    double GetWeight() const { return m_Weight; }
    double GetVolume() const { return m_Volume; }
    double GetBasePrice() const { return m_BasePrice; }

private:
    std::string m_Id;
    std::string m_Name;
    double m_Weight;
    double m_Volume;
    double m_BasePrice;
};
