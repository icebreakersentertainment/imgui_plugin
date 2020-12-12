#include <string>
#include <iostream>

//#include <imgui/imgui.h>
//#include "imgui/misc/cpp/imgui_stdlib.h"

#include "imguicolortextedit/TextEditor.hpp"


namespace ice_engine
{
namespace graphics
{
namespace gui
{

//static int InputTextCallback(ImGuiInputTextCallbackData* data)
//{
//    TextEditor* textEditor = static_cast<TextEditor*>(data->UserData);
//    return textEditor->inputTextCallback(data);
////    std::cout << "HERE "
////    << data->EventChar << " | "
////    << data->EventKey << " | "
////    << data->BufTextLen << " | "
////    << data->BufDirty << " | "
////    << std::endl;
////    return 0;
//}

TextEditor::TextEditor(const std::string& text)
{
    setText(text);
}

TextEditor::TextEditor(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string& text) : Component(x, y, width, height)
{
    setText(text);
}

void TextEditor::tick(const float32 delta)
{
    ImGui::PushID(uuid_.c_str());

    editor_.Render("TextEditor");

    if (callOnChangeCallback_)
    {
        onChangeCallback_();
        callOnChangeCallback_ = false;
    }

    ImGui::PopID();
}

void TextEditor::setText(const std::string& text)
{
    editor_.SetText(text);
}

const std::string& TextEditor::text() const
{
    return editor_.GetText();
}

void TextEditor::setSyntaxHighlighting(const SyntaxHighlighting syntaxHighlighting)
{
    switch (syntaxHighlighting)
    {
        case SyntaxHighlighting::CPlusPlus:
            syntaxHighlighting_ = SyntaxHighlighting::CPlusPlus;
            editor_.SetLanguageDefinition(::TextEditor::LanguageDefinition::CPlusPlus());
            break;

        case SyntaxHighlighting::GLSL:
            syntaxHighlighting_ = SyntaxHighlighting::GLSL;
            editor_.SetLanguageDefinition(::TextEditor::LanguageDefinition::GLSL());
            break;

        case SyntaxHighlighting::HLSL:
            syntaxHighlighting_ = SyntaxHighlighting::HLSL;
            editor_.SetLanguageDefinition(::TextEditor::LanguageDefinition::HLSL());
            break;

        case SyntaxHighlighting::C:
            syntaxHighlighting_ = SyntaxHighlighting::C;
            editor_.SetLanguageDefinition(::TextEditor::LanguageDefinition::C());
            break;

        case SyntaxHighlighting::SQL:
            syntaxHighlighting_ = SyntaxHighlighting::SQL;
            editor_.SetLanguageDefinition(::TextEditor::LanguageDefinition::SQL());
            break;

        case SyntaxHighlighting::AngelScript:
            syntaxHighlighting_ = SyntaxHighlighting::AngelScript;
            editor_.SetLanguageDefinition(::TextEditor::LanguageDefinition::AngelScript());
            break;

        case SyntaxHighlighting::Lua:
            syntaxHighlighting_ = SyntaxHighlighting::Lua;
            editor_.SetLanguageDefinition(::TextEditor::LanguageDefinition::Lua());
            break;

        default:
            syntaxHighlighting_ = SyntaxHighlighting::None;
            editor_.SetLanguageDefinition(::TextEditor::LanguageDefinition());
            break;
    }
}

SyntaxHighlighting TextEditor::syntaxHighlighting() const
{
    return syntaxHighlighting_;
}

void TextEditor::setCursorPosition(const int32 line, const int32 column)
{
    editor_.SetCursorPosition({line - 1, column});
}

void TextEditor::setOnChangeCallback(std::function<void()>& onChangeCallback)
{
    onChangeCallback_ = onChangeCallback;
}

int TextEditor::inputTextCallback(ImGuiInputTextCallbackData* data)
{
//    if (data->BufTextLen != text_.size())
//    {
////        std::cout << "HERE "
////            << data->EventChar << " | "
////            << data->EventKey << " | "
////            << data->BufTextLen << " | "
////            << data->BufDirty << " | "
////            << text_.size() << " | "
////            << std::endl;
//        // We can't just call the callback here because text_ hasn't actually changed yet
//        callOnChangeCallback_ = true;
//    }
////    std::cout << "HERE "
////        << data->EventChar << " | "
////        << data->EventKey << " | "
////        << data->BufTextLen << " | "
////        << data->BufDirty << " | "
////        << text_.size() << " | "
////        << std::endl;
    return 0;
}

}
}
}