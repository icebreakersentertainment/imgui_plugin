#ifndef TEXTFIELD_H_
#define TEXTFIELD_H_

#include <string>
#include <vector>

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

    virtual ~TextField() = default;

    virtual void tick(const float32 delta) override;

    virtual void setText(const std::string& text) override;
    virtual std::string getText() const override;

private:
    std::vector<char> textBuffer_;
    std::string text_;
};

}
}
}

#endif //TEXTFIELD_H_
