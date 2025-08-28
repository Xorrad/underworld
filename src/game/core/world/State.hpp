#pragma once

class State {
public:
    State(std::string id, std::string name, Color color, City* capital);

    std::string GetId() const;
    std::string GetName() const;
    Color GetColor() const;
    City* GetCapital();

private:
    std::string m_Id;
    std::string m_Name;
    Color m_Color;
    City* m_Capital;
};