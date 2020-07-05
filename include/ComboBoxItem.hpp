#ifndef COMBOBOXITEM_HPP_
#define COMBOBOXITEM_HPP_

#include "graphics/gui/IComboBoxItem.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class ComboBoxItem : public IComboBoxItem
{
public:
    ComboBoxItem() = default;
    ComboBoxItem(const std::string& label);
    ~ComboBoxItem() override = default;

    void setLabel(const std::string& label) override;
    const std::string& getLabel() const override;

private:
    std::string label_;
};

}
}
}

#endif //COMBOBOXITEM_HPP_
