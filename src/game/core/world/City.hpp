#pragma once

class City {
public:
    City(std::string id, std::string name, int population, Vec2<int> position);

    std::string GetId() const;
    std::string GetName() const;
    int GetPopulation() const;
    Vec2<int> GetPosition() const;

private:
    std::string m_Id;
    std::string m_Name;
    int m_Population;
    Vec2<int> m_Position;
};