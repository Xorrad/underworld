#pragma once

#include "IFaction.hpp"

class Military : public IFaction {
public:
    Military(const std::string& id, const std::string& name);

    virtual bool IsGovernmental() const override;

private:
};