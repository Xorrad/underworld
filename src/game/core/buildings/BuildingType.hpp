#pragma once

class BuildingType {
public:
    BuildingType(const std::string& id, const std::string& name, int price, int employees, BuildingTypes type, UniquePtr<ProductionChain> productionChain);
    BuildingType(const BuildingType& other);
    BuildingType(BuildingType&& other) noexcept = default;

    BuildingType& operator=(const BuildingType& other);
    BuildingType& operator=(BuildingType&& other) noexcept = default;

    const std::string& getId() const;
    const std::string& getName() const;
    int getPrice() const;
    int getEmployees() const;
    BuildingTypes getType() const;
    ProductionChain* getProductionChain();

    void setId(const std::string& id);
    void setName(const std::string& name);
    void setPrice(int price);
    void setEmployees(int employees);
    void setType(BuildingTypes type);
    void setProductionChain(UniquePtr<ProductionChain> productionChain);

private:
    std::string m_Id;
    std::string m_Name;
    int m_Price;
    int m_Employees;
    BuildingTypes m_Type;
    UniquePtr<ProductionChain> m_ProductionChain;
};