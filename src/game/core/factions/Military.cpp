#include "Military.hpp"

Military::Military(const std::string& id, const std::string& name) : IFaction(id, name, false) {}

bool Military::IsGovernmental() const {
    return true;
};;