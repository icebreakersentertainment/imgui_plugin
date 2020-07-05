#include "MenuItem.hpp"

#include "imgui.h"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

MenuItem::MenuItem(const std::string& label) : label_(label), callback_([]() {})
{
	initialize();
}

MenuItem::~MenuItem()
{

}

void MenuItem::initialize()
{

}

void MenuItem::tick(const float32 delta)
{
	if (components_.size() > 0)
	{
		if (ImGui::BeginMenu(label_.c_str(), !disabled_))
		{
			for (auto& c : components_) c->tick(delta);

			ImGui::EndMenu();
		}
	}
	else if (ImGui::MenuItem(label_.c_str(), "", false, !disabled_))
	{
		callback_();
	}
}

void MenuItem::setLabel(const std::string& label)
{
	label_ = label;
}

const std::string& MenuItem::getLabel() const
{
	return label_;
}

void MenuItem::setCallback(std::function<void()>& callback)
{
	callback_ = callback;
}

IMenuItem* MenuItem::createMenuItem(const std::string& label)
{
	auto menuItem = std::make_unique<MenuItem>(label);
	auto menuItemPtr = menuItem.get();

	components_.push_back( std::move(menuItem) );

	return menuItemPtr;
}

}
}
}
