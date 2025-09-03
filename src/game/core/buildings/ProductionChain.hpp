#pragma once

#include <nlohmann/json.hpp>

class ProductionChain {
public:
    ProductionChain(int duration, const Date& start, const std::unordered_map<Item*, int>& inputs, const std::unordered_map<Item*, int>& outputs);
    ProductionChain(const ProductionChain& other);

    ProductionChain& operator=(const ProductionChain& other);

    int GetDuration() const;
    const Date& GetStart() const;
    const std::unordered_map<Item*, int>& GetInputs() const;
    const std::unordered_map<Item*, int>& GetOutputs() const;

    void SetDuration(int duration);
    void SetStart(const Date& start);
    void SetInputs(const std::unordered_map<Item*, int>& inputs);
    void SetOutputs(const std::unordered_map<Item*, int>& outputs);

    static UniquePtr<ProductionChain> FromJson(World* world, const nlohmann::json& json);

private:
    int m_Duration; // in days
    Date m_Start;
    std::unordered_map<Item*, int> m_Inputs;
    std::unordered_map<Item*, int> m_Outputs;
};
