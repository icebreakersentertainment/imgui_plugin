#include <string>
#include <iostream>

#include <imgui/imgui.h>
#include "imgui/misc/cpp/imgui_stdlib.h"

#include "TextField.hpp"


namespace ice_engine
{
namespace graphics
{
namespace gui
{

static int InputTextCallback(ImGuiInputTextCallbackData* data)
{
    TextField* textField = static_cast<TextField*>(data->UserData);
    return textField->inputTextCallback(data);
//    std::cout << "HERE "
//    << data->EventChar << " | "
//    << data->EventKey << " | "
//    << data->BufTextLen << " | "
//    << data->BufDirty << " | "
//    << std::endl;
//    return 0;
}

TextField::TextField(const std::string& text)
{
    setText(text);
}

TextField::TextField(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string& text) : Component(x, y, width, height)
{
    setText(text);
}

void TextField::tick(const float32 delta)
{
    ImGui::PushID(uuid_.c_str());

    ImGui::InputText("", &text_, ImGuiInputTextFlags_CallbackAlways, InputTextCallback, this);

    if (callOnChangeCallback_)
    {
        onChangeCallback_();
        callOnChangeCallback_ = false;
    }

    ImGui::PopID();
}

void TextField::setText(const std::string& text)
{
    text_ = text;
}

const std::string& TextField::text() const
{
    return text_;
}

void TextField::setOnChangeCallback(std::function<void()>& onChangeCallback)
{
    onChangeCallback_ = onChangeCallback;
}

int TextField::inputTextCallback(ImGuiInputTextCallbackData* data)
{
    if (data->BufTextLen != text_.size())
    {
//        std::cout << "HERE "
//            << data->EventChar << " | "
//            << data->EventKey << " | "
//            << data->BufTextLen << " | "
//            << data->BufDirty << " | "
//            << text_.size() << " | "
//            << std::endl;
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