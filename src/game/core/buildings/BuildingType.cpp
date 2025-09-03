#include "BuildingType.hpp"
#include "ProductionChain.hpp"

BuildingType::BuildingType(const std::string& id, const std::string& name, int price, int employees, BuildingTypes type, UniquePtr<ProductionChain> productionChain) :
    m_Id(id),
    m_Name(name),
    m_Price(price),
    m_Employees(employees),
    m_Type(type),
    m_ProductionChain(std::move(productionChain))
{}

BuildingType::BuildingType(const BuildingType& other) :
    m_Id(other.m_Id),
    m_Name(other.m_Name),
    m_Price(other.m_Price),
    m_Employees(other.m_Employees),
    m_Type(other.m_Type),
    m_ProductionChain(other.m_ProductionChain ? MakeUnique<ProductionChain>(*other.m_ProductionChain) : nullptr)
{}

BuildingType& BuildingType::operator=(const BuildingType& other) {
    if (this != &other) {
        m_Id = other.m_Id;
        m_Name = other.m_Name;
        m_Price = other.m_Price;
        m_Employees = other.m_Employees;
        m_Type = other.m_Type;
        m_ProductionChain = other.m_ProductionChain ? MakeUnique<ProductionChain>(*other.m_ProductionChain) : nullptr;
    }
    return *this;
}

const std::string& BuildingType::GetId() const {
    return m_Id;
}

const std::string& BuildingType::GetName() const {
    return m_Name;
}

int BuildingType::GetPrice() const {
    return m_Price;
}

BuildingTypes BuildingType::GetType() const {
    return m_Type;
}

int BuildingType::GetEmployees() const {
    return m_Employees;
}

ProductionChain* BuildingType::GetProductionChain() {
    return m_ProductionChain.get();
}

void BuildingType::SetId(const std::string& id) {
    m_Id = id;
}

void BuildingType::SetName(const std::string& name) {
    m_Name = name;
}

void BuildingType::SetPrice(int price) {
    m_Price = price;
}

void BuildingType::SetType(BuildingTypes type) {
    m_Type = type;
}

void BuildingType::SetEmployees(int employees) {
    m_Employees = employees;
}

void BuildingType::SetProductionChain(UniquePtr<ProductionChain> productionChain) {
    m_ProductionChain = std::move(productionChain);
}
