#include "ComboBoxItem.hpp"
#include "../include/ComboBoxItem.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

ComboBoxItem::ComboBoxItem(const std::string& label) : label_(label)
{
}

void ComboBoxItem::setLabel(const std::string& label)
{
    label_ = label;
}

const std::string& ComboBoxItem::getLabel() const
{
    return label_;
}

}
}
}
