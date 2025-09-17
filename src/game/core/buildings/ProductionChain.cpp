#include "ProductionChain.hpp"
#include "game/core/world/World.hpp"
#include "game/core/items/Item.hpp"
#include "game/core/items/Stockpile.hpp"

ProductionChain::ProductionChain(int duration, const std::unordered_map<Item*, int>& inputs, const std::unordered_map<Item*, int>& outputs) :
    m_Duration(duration),
    m_Inputs(inputs),
    m_Outputs(outputs)
{}

ProductionChain::ProductionChain(const ProductionChain& other) :
    m_Duration(other.m_Duration),
    m_Inputs(other.m_Inputs),
    m_Outputs(other.m_Outputs)
{}

ProductionChain& ProductionChain::operator=(const ProductionChain& other) {
    if (this != &other) {
        m_Duration = other.m_Duration;
        m_Inputs = other.m_Inputs;
        m_Outputs = other.m_Outputs;
    }
    return *this;
}

int ProductionChain::GetDuration() const {
    return m_Duration;
}

const std::unordered_map<Item*, int>& ProductionChain::GetInputs() const {
    return m_Inputs;
}

const std::unordered_map<Item*, int>& ProductionChain::GetOutputs() const {
    return m_Outputs;
}

bool ProductionChain::HasInputs(Stockpile* stockpile) {
    return m_Inputs.empty() || std::all_of(
        m_Inputs.begin(),
        m_Inputs.end(),
        [&](auto const& input) {
            auto const& [itemType, quantity] = input;
            return stockpile->Contains(itemType, quantity);
        }
    );
}

void ProductionChain::SetDuration(int duration) {
    m_Duration = duration;
}

void ProductionChain::SetInputs(const std::unordered_map<Item*, int>& inputs) {
    m_Inputs = inputs;
}

void ProductionChain::SetOutputs(const std::unordered_map<Item*, int>& outputs) {
    m_Outputs = outputs;
}

UniquePtr<ProductionChain> ProductionChain::FromJson(World* world, const nlohmann::json& json) {
    int duration;
    std::unordered_map<Item*, int> inputs;
    std::unordered_map<Item*, int> outputs;

    if (!json.contains("duration"))
        throw std::runtime_error("Production chain for building is missing 'duration' field");
    if (!json.contains("input"))
        throw std::runtime_error("Production chain for building is missing 'input' field");
    if (!json.contains("output"))
        throw std::runtime_error("Production chain for building is missing 'output' field");

    duration = json["duration"];

    for (auto& [itemId, amount] : json["input"].items()) {
        if (!world->GetItems().contains(itemId)) {
            // TODO: add warning message when logging system is done.
            continue;
        }
        inputs[world->GetItems()[itemId].get()] = amount;
    }
    
    for (auto& [itemId, amount] : json["output"].items()) {
        if (!world->GetItems().contains(itemId)) {
            // TODO: add warning message when logging system is done.
            continue;
        }
        outputs[world->GetItems()[itemId].get()] = amount;
    }

    return MakeUnique<ProductionChain>(duration, inputs, outputs);
}