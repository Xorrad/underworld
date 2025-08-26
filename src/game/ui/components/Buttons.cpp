#include "Buttons.hpp"

bool tuim::HomeMenuButton(const std::string& id, const std::string& text) {
    std::shared_ptr<Frame> frame = tuim::GetCurrentFrame();

    // Create a new item and push it to the stack.
    ItemId itemId = tuim::StringToId(id);
    std::shared_ptr<Item> item = std::make_shared<Item>();
    item->m_Id = itemId;
    item->m_Size = vec2(tuim::CalcTextWidth(text), 1);
    item->m_Pos = frame->m_Cursor;
    item->m_Flags = ITEM_FLAGS_NONE;
    tuim::AddItem(item);

    if (tuim::IsItemHovered()) {
        if (tuim::IsKeyPressed(tuim::ENTER)) {
            tuim::SetActiveItemId(item->m_Id);
        }
        tuim::Print("> ");
    }
    else tuim::Print("  ");

    tuim::Print("{}&r", text);

    return tuim::IsItemActive();
}