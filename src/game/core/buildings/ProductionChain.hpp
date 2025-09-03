#pragma once

#include <nlohmann/json.hpp>

class ProductionChain {
public:
    ProductionChain(int duration, const Date& start, const std::unordered_map<Item*, int>& inputs, const std::unordered_map<Item*, int>& outputs);
    ProductionChain(const ProductionChain& other);

    ProductionChain& operator=(const ProductionChain& other);

    int getDuration() const;
    const Date& getStart() const;
    const std::unordered_map<Item*, int>& getInputs() const;
    const std::unordered_map<Item*, int>& getOutputs() const;

    void setDuration(int duration);
    void setStart(const Date& start);
    void setInputs(const std::unordered_map<Item*, int>& inputs);
    void setOutputs(const std::unordered_map<Item*, int>& outputs);

    static UniquePtr<ProductionChain> FromJson(World* world, const nlohmann::json& json);

private:
    int m_Duration; // in days
    Date m_Start;
    std::unordered_map<Item*, int> m_Inputs;
    std::unordered_map<Item*, int> m_Outputs;
};
