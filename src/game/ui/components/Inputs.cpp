#include "Inputs.hpp"
#include "game/core/world/Scenario.hpp"

bool tuim::ScenarioInput(const std::string& id, std::string_view fmt, size_t* index, const std::vector<UniquePtr<Scenario>>& entries) {
    std::shared_ptr<Frame> frame = tuim::GetCurrentFrame();

    // Create a new item and push it to the stack.
    ItemId itemId = tuim::StringToId(id);
    std::shared_ptr<Item> item = std::make_shared<Item>();
    item->m_Id = itemId;
    item->m_Pos = frame->m_Cursor;
    item->m_Flags = ITEM_FLAGS_NONE;
    tuim::AddItem(item);

    bool hasChanged = false;

    if (*index < 0) *index = 0;
    else if (*index > entries.size()) *index = entries.size()-1;
        
    if (tuim::IsItemHovered()) {
        if (tuim::IsKeyPressed(Key::LEFT)) {
            if (!entries.empty()) {
                if (*index == 0) *index = entries.size() - 1;
                else *index = *index - 1;
                hasChanged = true;
            }
        }
        else if (tuim::IsKeyPressed(Key::RIGHT)) {
            if (!entries.empty()) {
                if (*index == entries.size()-1) *index = 0;
                else *index = *index + 1;
                hasChanged = true;
            }
        }
        else if (tuim::IsKeyPressed(Key::ENTER)) {
            if (tuim::IsItemActive()) {
                tuim::SetActiveItemId(0);
                hasChanged = true;
            }
            else {
                tuim::SetActiveItemId(item->m_Id);
            }
        }
        if (tuim::IsItemActive()) tuim::Print("[*] ");
        else tuim::Print("[x] ");
    }
    else tuim::Print("[ ] ");

    std::string text = std::vformat(fmt, std::make_format_args((entries.empty() ? "No Scenario Available" : entries.at(*index)->GetName())));
    item->m_Size = vec2(tuim::CalcTextWidth(text), 1);
    
    tuim::Print(text);

    return hasChanged;
}