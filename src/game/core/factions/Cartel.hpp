#pragma once

#include "IFaction.hpp"

class Cartel : public IFaction {
public:
    Cartel(const std::string& id, const std::string& name, bool isPlayer);

    virtual bool IsGovernmental() const override;

private:
};