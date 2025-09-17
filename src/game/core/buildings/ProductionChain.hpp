#pragma once

#include <nlohmann/json.hpp>

class ProductionChain {
public:
    ProductionChain(int duration, const std::unordered_map<Item*, int>& inputs, const std::unordered_map<Item*, int>& outputs);
    ProductionChain(const ProductionChain& other);

    ProductionChain& operator=(const ProductionChain& other);

    int GetDuration() const;
    const std::unordered_map<Item*, int>& GetInputs() const;
    const std::unordered_map<Item*, int>& GetOutputs() const;
    bool HasInputs(Stockpile* stockpile);

    void SetDuration(int duration);
    void SetInputs(const std::unordered_map<Item*, int>& inputs);
    void SetOutputs(const std::unordered_map<Item*, int>& outputs);

    static UniquePtr<ProductionChain> FromJson(World* world, const nlohmann::json& json);

private:
    int m_Duration; // in days
    std::unordered_map<Item*, int> m_Inputs;
    std::unordered_map<Item*, int> m_Outputs;
};
