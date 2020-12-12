#ifndef TEXTAREA_HPP_
#define TEXTAREA_HPP_

#include <string>
#include <vector>

#include "graphics/gui/ITextArea.hpp"

#include "Component.hpp"
#include "Types.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class TextArea : public Component, public ITextArea
{
public:
    TextArea(const std::string& text = std::string());
    TextArea(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string& text = std::string());

    virtual ~TextArea() = default;

    virtual void tick(const float32 delta) override;

    virtual void setText(const std::string& text) override;
    virtual const std::string& text() const override;

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

    bool callOnChangeCallback_ = false;
    std::function<void()> onChangeCallback_ = []() {};
};

}
}
}


#endif //TEXTAREA_HPP_
