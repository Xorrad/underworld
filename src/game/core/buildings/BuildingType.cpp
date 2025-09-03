#include "BuildingType.hpp"
#include "ProductionChain.hpp"

BuildingType::BuildingType(const std::string& id, const std::string& name, int price, int employees, BuildingTypes type, UniquePtr<ProductionChain> productionChain) :
    m_Id(id),
    m_Name(name),
    m_Price(price),
    m_Type(type),
    m_Employees(employees),
    m_ProductionChain(std::move(productionChain))
{}

BuildingType::BuildingType(const BuildingType& other) :
    m_Id(other.m_Id),
    m_Name(other.m_Name),
    m_Price(other.m_Price),
    m_Type(other.m_Type),
    m_Employees(other.m_Employees),
    m_ProductionChain(other.m_ProductionChain ? MakeUnique<ProductionChain>(*other.m_ProductionChain) : nullptr)
{}

BuildingType& BuildingType::operator=(const BuildingType& other) {
    if (this != &other) {
        m_Id = other.m_Id;
        m_Name = other.m_Name;
        m_Price = other.m_Price;
        m_Type = other.m_Type;
        m_Employees = other.m_Employees;
        m_ProductionChain = other.m_ProductionChain ? MakeUnique<ProductionChain>(*other.m_ProductionChain) : nullptr;
    }
    return *this;
}

const std::string& BuildingType::getId() const {
    return m_Id;
}

const std::string& BuildingType::getName() const {
    return m_Name;
}

int BuildingType::getPrice() const {
    return m_Price;
}

BuildingTypes BuildingType::getType() const {
    return m_Type;
}

int BuildingType::getEmployees() const {
    return m_Employees;
}

ProductionChain* BuildingType::getProductionChain() {
    return m_ProductionChain.get();
}

void BuildingType::setId(const std::string& id) {
    m_Id = id;
}

void BuildingType::setName(const std::string& name) {
    m_Name = name;
}

void BuildingType::setPrice(int price) {
    m_Price = price;
}

void BuildingType::setType(BuildingTypes type) {
    m_Type = type;
}

void BuildingType::setEmployees(int employees) {
    m_Employees = employees;
}

void BuildingType::setProductionChain(UniquePtr<ProductionChain> productionChain) {
    m_ProductionChain = std::move(productionChain);
}
