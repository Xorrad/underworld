#pragma once

class Country {
public:
    Country(std::string id, std::string name, City* capital, std::vector<State*> states);

    std::string GetId() const;
    std::string GetName() const;
    City* GetCapital();
    std::vector<State*> GetStates();

private:
    std::string m_Id;
    std::string m_Name;
    City* m_Capital;
    std::vector<State*> m_States;
};