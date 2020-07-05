#include <algorithm>

#include "GenericComponentContainer.hpp"

#include "Label.hpp"
#include "Button.hpp"
#include "TextField.hpp"
#include "ComboBox.hpp"
#include "TreeView.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{
namespace
{
template <typename T, typename ... Args>
T* create(std::vector<std::unique_ptr<IComponent>>& components, const Args ... args)
{
    auto c = std::make_unique<T>(args ...);
    auto ptr = c.get();
    components.push_back( std::move(c) );

    return ptr;
}

template <typename T>
void destroy(std::vector<std::unique_ptr<IComponent>>& components, const T* t)
{
    components.erase(
        std::remove_if(
                components.begin(),
                components.end(),
                [t](const std::unique_ptr<IComponent>& c) {
                    return c.get() == t;
                }
        ),
        components.end()
    );
}
}

GenericComponentContainer::GenericComponentContainer(const uint32 x, const uint32 y, const uint32 width, const uint32 height)
:
	Component::Component(x, y, width, height)
{

}

void GenericComponentContainer::initialize()
{

}

ILabel* GenericComponentContainer::createLabel(const std::string label)
{
	auto l = std::make_unique<Label>(label);
	auto labelPtr = l.get();
	components_.push_back( std::move(l) );

	return labelPtr;
}

ILabel* GenericComponentContainer::createLabel(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string label)
{
	auto l = std::make_unique<Label>(x, y, width, height, label);
	auto labelPtr = l.get();
	components_.push_back( std::move(l) );

	return labelPtr;
}

IButton* GenericComponentContainer::createButton(const std::string label)
{
	auto button = std::make_unique<Button>(label);
	auto buttonPtr = button.get();
	components_.push_back( std::move(button) );

	return buttonPtr;
}

IButton* GenericComponentContainer::createButton(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string label)
{
	auto button = std::make_unique<Button>(x, y, width, height, label);
	auto buttonPtr = button.get();
	components_.push_back( std::move(button) );

	return buttonPtr;
}

ITextField* GenericComponentContainer::createTextField(const std::string label)
{
    return create<TextField>(components_, label);
}

ITreeView* GenericComponentContainer::createTreeView()
{
    return create<TreeView>(components_);
}

ITextField* GenericComponentContainer::createTextField(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string label)
{
    return create<TextField>(components_, x, y, width, height, label);
}

IComboBox* GenericComponentContainer::createComboBox()
{
    return create<ComboBox>(components_);
}

void GenericComponentContainer::destroy(const ILabel* label)
{
	components_.erase(
		std::remove_if(
			components_.begin(),
			components_.end(),
			[label](const std::unique_ptr<IComponent>& c) {
				return c.get() == label;
			}
		),
		components_.end()
	);
}

void GenericComponentContainer::destroy(const IButton* button)
{
	components_.erase(
		std::remove_if(
			components_.begin(),
			components_.end(),
			[button](const std::unique_ptr<IComponent>& c) {
				return c.get() == button;
			}
		),
		components_.end()
	);
}

void GenericComponentContainer::destroy(const ITextField* textField)
{
	gui::destroy(components_, textField);
}

void GenericComponentContainer::destroy(const ITreeView* treeView)
{
	gui::destroy(components_, treeView);
}

void GenericComponentContainer::destroy(const IComboBox* comboBox)
{
	gui::destroy(components_, comboBox);
}

}
}
}
