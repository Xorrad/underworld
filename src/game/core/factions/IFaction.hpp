#pragma once

class IFaction {
public:
    IFaction(const std::string& id, const std::string& name, bool isPlayer);
    virtual ~IFaction() {}

    std::string GetId() const;
    std::string GetName() const;
    bool IsPlayer() const;
    
    virtual bool IsGovernmental() const = 0;

    void SetName(const std::string& name);

private:
    std::string m_Id;
    std::string m_Name;
    bool m_IsPlayer;
    std::vector<IFaction> m_Allies;
};