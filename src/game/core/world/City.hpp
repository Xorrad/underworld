#pragma once

class City {
public:
    City(std::string id, std::string name);

    std::string GetId() const;
    std::string GetName() const;

private:
    std::string m_Id;
    std::string m_Name;
};