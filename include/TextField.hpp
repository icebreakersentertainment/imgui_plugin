#ifndef TEXTFIELD_H_
#define TEXTFIELD_H_

#include <string>
#include <vector>

#include <imgui/imgui.h>

#include "graphics/gui/ITextField.hpp"

#include "Component.hpp"
#include "Types.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class TextField : public Component, public ITextField
{
public:
    TextField(const std::string& text = std::string());
    TextField(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string& text = std::string());

    virtual ~TextField() override = default;

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

#endif //TEXTFIELD_H_
