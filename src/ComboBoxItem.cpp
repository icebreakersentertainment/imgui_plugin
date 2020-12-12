#include "ComboBoxItem.hpp"

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

const std::string& ComboBoxItem::label() const
{
    return label_;
}

}
}
}
