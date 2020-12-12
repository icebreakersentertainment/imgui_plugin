#include <algorithm>

#include <imgui/imgui.h>

#include "ComboBox.hpp"
#include "ComboBoxItem.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

void ComboBox::tick(const float32 delta)
{
    const std::string& currentItemLabel = selected_ != nullptr ? selected_->label() : "";

    ImGui::PushID(uuid_.c_str());

    if (ImGui::BeginCombo("", currentItemLabel.c_str()))
    {
        for (const auto& item : comboBoxItems_)
        {
            bool isSelected = (selected_ == item.get());

            if (ImGui::Selectable(item->label().c_str(), isSelected))
            {
                selected_ = item.get();
                callback_(selected_);
            }

            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    ImGui::PopID();
}

IComboBoxItem* ComboBox::createItem(const std::string& label)
{
    auto comboBoxItem = std::make_unique<ComboBoxItem>(label);
    auto comboBoxItemPtr = comboBoxItem.get();
    comboBoxItems_.push_back( std::move(comboBoxItem) );

    return comboBoxItemPtr;
}

IComboBoxItem* ComboBox::getItem(const std::string& label) const
{
    auto func = [&label](const auto& cbi) {
        return cbi->label() == label;
    };

    auto it = std::find_if(comboBoxItems_.begin(), comboBoxItems_.end(), func);

    if (it != comboBoxItems_.end())
    {
        return it->get();
    }

    return nullptr;
}

void ComboBox::destroy(const IComboBoxItem* comboBoxItem)
{
    auto func = [comboBoxItem](const auto& cbi) {
        return cbi.get() == comboBoxItem;
    };

    auto it = std::find_if(comboBoxItems_.begin(), comboBoxItems_.end(), func);

    if (it != comboBoxItems_.end())
    {
        comboBoxItems_.erase(it);
    }
}

void ComboBox::select(IComboBoxItem* comboBoxItem)
{
    selected_ = comboBoxItem;
}

void ComboBox::unselect(const IComboBoxItem* comboBoxItem)
{
    if (selected_ == comboBoxItem)
    {
        selected_ = nullptr;
    }
}

bool ComboBox::selected(const IComboBoxItem* comboBoxItem) const
{
    return selected_ == comboBoxItem;
}

void ComboBox::setCallback(std::function<void(IComboBoxItem*)>& callback)
{
    callback_ = callback;
}

}
}
}
