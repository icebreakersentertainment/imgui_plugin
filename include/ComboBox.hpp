#ifndef COMBOBOX_HPP_
#define COMBOBOX_HPP_

#include <vector>
#include <memory>

#include "graphics/gui/IComboBox.hpp"

#include "Component.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class ComboBox : public Component, public IComboBox
{
public:
    ~ComboBox() override = default;

    void tick(const float32 delta) override;

    IComboBoxItem* createItem(const std::string& label) override;
    IComboBoxItem* getItem(const std::string& label) const override;
    void destroy(const IComboBoxItem* comboBoxItem) override;

    void select(IComboBoxItem* comboBoxItem) override;
    void unselect(const IComboBoxItem* comboBoxItem) override;
    bool selected(const IComboBoxItem* comboBoxItem) const override;

    void setCallback(std::function<void(IComboBoxItem*)>& callback) override;

private:
    std::function<void(IComboBoxItem*)> callback_ = [](IComboBoxItem*) {};
    std::vector<std::unique_ptr<IComboBoxItem>> comboBoxItems_;
    IComboBoxItem* selected_ = nullptr;

};

}
}
}

#endif //COMBOBOX_HPP_
