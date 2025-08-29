#pragma once

namespace tuim {
    bool ScenarioInput(const std::string& id, std::string_view fmt, size_t* index, const std::vector<UniquePtr<Scenario>>& entries);
}