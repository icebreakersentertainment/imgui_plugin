#ifndef TEXTEDITOR_HPP_
#define TEXTEDITOR_HPP_

#include <string>
#include <vector>

#include <imgui/imgui.h>

#include <TextEditor.h>

#include "ITextEditor.hpp"

#include "Component.hpp"
#include "Types.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class TextEditor : public Component, public ITextEditor
{
public:
    TextEditor(const std::string& text = std::string());
    TextEditor(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string& text = std::string());

    virtual ~TextEditor() override = default;

    virtual void tick(const float32 delta) override;

    virtual void setText(const std::string& text) override;
    virtual const std::string& text() const override;

    virtual void setSyntaxHighlighting(const SyntaxHighlighting syntaxHighlighting) override;
    virtual SyntaxHighlighting syntaxHighlighting() const override;

    virtual void setCursorPosition(const int32 line, const int32 column) override;

    virtual void setOnChangeCallback(std::function<void()>& onChangeCallback) override;

    /**
     * For internal use only.
     *
     * @param data
     * @return
     */
    int inputTextCallback(ImGuiInputTextCallbackData* data);
private:
    std::string text_;
    ::TextEditor editor_;

    SyntaxHighlighting syntaxHighlighting_ = SyntaxHighlighting::None;

    bool callOnChangeCallback_ = false;
    std::function<void()> onChangeCallback_ = []() {};
};

}
}
}

#endif //TEXTEDITOR_HPP_
