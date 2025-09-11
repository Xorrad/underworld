#pragma once

class BuildingType {
public:
    BuildingType(const std::string& id, const std::string& name, const std::string& icon, int price, int employees, int maxVolume, BuildingTypes type, UniquePtr<ProductionChain> productionChain);
    BuildingType(const BuildingType& other);
    BuildingType(BuildingType&& other) noexcept = default;

    BuildingType& operator=(const BuildingType& other);
    BuildingType& operator=(BuildingType&& other) noexcept = default;

    const std::string& GetId() const;
    const std::string& GetName() const;
    const std::string& GetIcon() const;
    int GetPrice() const;
    int GetEmployees() const;
    int GetMaxVolume() const;
    BuildingTypes GetType() const;
    ProductionChain* GetProductionChain();

    void SetId(const std::string& id);
    void SetName(const std::string& name);
    void SetIcon(const std::string& icon);
    void SetPrice(int price);
    void SetEmployees(int employees);
    void SetMaxVolume(int maxVolume);
    void SetType(BuildingTypes type);
    void SetProductionChain(UniquePtr<ProductionChain> productionChain);

private:
    std::string m_Id;
    std::string m_Name;
    std::string m_Icon;
    int m_Price;
    int m_Employees;
    int m_MaxVolume;
    BuildingTypes m_Type;
    UniquePtr<ProductionChain> m_ProductionChain;
};