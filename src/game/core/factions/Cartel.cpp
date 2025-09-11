#include "Cartel.hpp"

Cartel::Cartel(const std::string& id, const std::string& name, bool isPlayer) : IFaction(id, name, isPlayer) {}

bool Cartel::IsGovernmental() const {
    return false;
};