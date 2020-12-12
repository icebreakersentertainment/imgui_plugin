#ifndef ITEXTEDITOR_HPP_
#define ITEXTEDITOR_HPP_

#include <string>
#include <functional>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "graphics/gui/IComponent.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

enum SyntaxHighlighting
{
    None = 0,

    CPlusPlus,
    HLSL,
    GLSL,
    C,
    SQL,
    AngelScript,
    Lua
};

class ITextEditor : public virtual IComponent
{
public:
    virtual ~ITextEditor() = default;

    virtual void setText(const std::string& text) = 0;
    virtual const std::string& text() const  = 0;

    virtual void setSyntaxHighlighting(const SyntaxHighlighting syntaxHighlighting) = 0;
    virtual SyntaxHighlighting syntaxHighlighting() const = 0;

    virtual void setCursorPosition(const int32 line, const int32 column) = 0;

    virtual void setOnChangeCallback(std::function<void()>& onChangeCallback) = 0;
};

}
}
}

#endif //ITEXTEDITOR_HPP_
