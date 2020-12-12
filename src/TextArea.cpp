#include <string>
#include <iostream>

#include <imgui/imgui.h>
#include "imgui/misc/cpp/imgui_stdlib.h"

#include "TextArea.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

static int InputTextCallback(ImGuiInputTextCallbackData* data)
{
    TextArea* textArea = static_cast<TextArea*>(data->UserData);
    return textArea->inputTextCallback(data);
//    std::cout << "HERE "
//    << data->EventChar << " | "
//    << data->EventKey << " | "
//    << data->BufTextLen << " | "
//    << data->BufDirty << " | "
//    << std::endl;
//    return 0;
}

TextArea::TextArea(const std::string& text)
{
    setText(text);
}

TextArea::TextArea(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string& text) : Component(x, y, width, height)
{
    setText(text);
}

void TextArea::tick(const float32 delta)
{
    ImGui::PushID(uuid_.c_str());

    ImGui::InputTextMultiline("", &text_, {static_cast<float32>(width_), static_cast<float32>(height_)}, ImGuiInputTextFlags_CallbackAlways, InputTextCallback, this);

    if (callOnChangeCallback_)
    {
        onChangeCallback_();
        callOnChangeCallback_ = false;
    }

    ImGui::PopID();
}

void TextArea::setText(const std::string& text)
{
    text_ = text;
}

const std::string& TextArea::text() const
{
    return text_;
}

void TextArea::setOnChangeCallback(std::function<void()>& onChangeCallback)
{
    onChangeCallback_ = onChangeCallback;
}

int TextArea::inputTextCallback(ImGuiInputTextCallbackData* data)
{
    if (data->BufTextLen != text_.size())
    {
//        std::cout << "HERE "
//                  << data->EventChar << " | "
//                  << data->EventKey << " | "
//                  << data->BufTextLen << " | "
//                  << data->BufDirty << " | "
//                  << text_.size() << " | "
//                  << std::endl;
        // We can't just call the callback here because text_ hasn't actually changed yet
        callOnChangeCallback_ = true;
    }
//    std::cout << "HERE "
//        << data->EventChar << " | "
//        << data->EventKey << " | "
//        << data->BufTextLen << " | "
//        << data->BufDirty << " | "
//        << text_.size() << " | "
//        << std::endl;
    return 0;
}

}
}
}