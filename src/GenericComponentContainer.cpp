#include <algorithm>
#include <memory>

#include "GenericComponentContainer.hpp"

#include "Label.hpp"
#include "Button.hpp"
#include "TextField.hpp"
#include "TextArea.hpp"
#include "ComboBox.hpp"
#include "TreeView.hpp"
#include "imguicolortextedit/TextEditor.hpp"

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

ITreeView* GenericComponentContainer::createTreeView()
{
    return create<TreeView>(components_);
}

ITextField* GenericComponentContainer::createTextField(const std::string label)
{
    return create<TextField>(components_, label);
}

ITextField* GenericComponentContainer::createTextField(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string label)
{
    return create<TextField>(components_, x, y, width, height, label);
}

ITextArea* GenericComponentContainer::createTextArea(const std::string label)
{
    return create<TextArea>(components_, label);
}

ITextArea* GenericComponentContainer::createTextArea(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string label)
{
    return create<TextArea>(components_, x, y, width, height, label);
}

IComboBox* GenericComponentContainer::createComboBox()
{
    return create<ComboBox>(components_);
}

ITextEditor* GenericComponentContainer::createTextEditor(const std::string text)
{
    return create<TextEditor>(components_, text);
}

ITextEditor* GenericComponentContainer::createTextEditor(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string text)
{
    return create<TextEditor>(components_, x, y, width, height, text);
}

void GenericComponentContainer::add(std::unique_ptr <IComponent> component)
{
    components_.push_back(std::move(component));
}

void GenericComponentContainer::destroy(const ILabel* label)
{
    gui::destroy(components_, label);
//	components_.erase(
//		std::remove_if(
//			components_.begin(),
//			components_.end(),
//			[label](const std::unique_ptr<IComponent>& c) {
//				return c.get() == label;
//			}
//		),
//		components_.end()
//	);
}

void GenericComponentContainer::destroy(const IButton* button)
{
    gui::destroy(components_, button);
//	components_.erase(
//		std::remove_if(
//			components_.begin(),
//			components_.end(),
//			[button](const std::unique_ptr<IComponent>& c) {
//				return c.get() == button;
//			}
//		),
//		components_.end()
//	);
}

void GenericComponentContainer::destroy(const ITextField* textField)
{
	gui::destroy(components_, textField);
}

void GenericComponentContainer::destroy(const ITextArea* textArea)
{
	gui::destroy(components_, textArea);
}

void GenericComponentContainer::destroy(const ITreeView* treeView)
{
	gui::destroy(components_, treeView);
}

void GenericComponentContainer::destroy(const IComboBox* comboBox)
{
	gui::destroy(components_, comboBox);
}

std::unique_ptr<IComponent> GenericComponentContainer::remove(const IComponent* component)
{
    auto it = std::remove_if(
        components_.begin(),
        components_.end(),
        [component](const std::unique_ptr<IComponent>& c) {
            return c.get() == component;
        }
    );

    auto returnValue = std::move(*it);

    components_.erase(it);

    return std::move(returnValue);
}
}
}
}
