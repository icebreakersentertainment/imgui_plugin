#include <string>
#include <iostream>

#include "imgui.h"
#include "imgui/misc/cpp/imgui_stdlib.h"

#include "TextField.hpp"
#include "../include/TextField.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

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
    ImGui::InputText("", &text_);
}

void TextField::setText(const std::string& text)
{
    // 'Zero out' contents of buffer
    textBuffer_ = std::vector<char>(text.begin(), text.end());
    textBuffer_.reserve(255);
//    textBuffer_ = std::vector<char>(255, ' ');

//    std::copy(text.begin(), text.end(), std::front_inserter(textBuffer_));

    text_ = text;
}

std::string TextField::getText() const
{
    return std::string(textBuffer_.data());
}

}
}
}