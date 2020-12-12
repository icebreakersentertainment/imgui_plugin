#ifndef ITEXTEDITORFACTORY_HPP_
#define ITEXTEDITORFACTORY_HPP_

#include <string>

#include "ITextEditor.hpp"

#include "Types.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class ITextEditorFactory
{
public:
    virtual ~ITextEditorFactory() = default;

    virtual ITextEditor* createTextEditor(const std::string text = std::string()) = 0;
    virtual ITextEditor* createTextEditor(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string text = std::string()) = 0;
};

}
}
}

#endif //ITEXTEDITORFACTORY_HPP_
