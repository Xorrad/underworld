#pragma once

class Building {
public:
    Building(BuildingType* type, const Vec2<int>& position);

    BuildingType* GetType() const;
    const Vec2<int>& GetPosition() const;
    Stockpile* GetStockpile();
    Date GetProductionStartDate() const;
    Date GetProductionEndDate() const;

    void SetType(BuildingType* type);
    void SetPosition(const Vec2<int>& position);
    void SetProductionStartDate(const Date& date);

private:
    BuildingType* m_Type;
    Vec2<int> m_Position;
    UniquePtr<Stockpile> m_Stockpile;
    Date m_ProductionStartDate;
};