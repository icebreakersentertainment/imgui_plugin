#include "Menu.hpp"

#include "imgui.h"

#include "MenuItem.hpp"
#include "Separator.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

Menu::Menu(const std::string& label) : label_(label)
{
	initialize();
}

Menu::~Menu()
{
	
}

void Menu::initialize()
{
	
}

void Menu::tick(const float32 delta)
{
	if (ImGui::BeginMenu(label_.c_str()))
	{
		for (auto& c : components_)
		{
			c->tick(delta);
		}
		
		ImGui::EndMenu();
	}
}

void Menu::setLabel(const std::string& label)
{
	label_ = label;
}

const std::string& Menu::getLabel() const 
{
	return label_;
}

IMenu* Menu::createMenu(const std::string& label)
{
	auto menu = std::make_unique<Menu>(label);	
	auto menuPtr = menu.get();
	
	components_.push_back( std::move(menu) );
	
	return menuPtr;
}

IMenu* Menu::getMenu(const std::string& label) const
{
	return nullptr;
}

void Menu::createSeparator()
{
	auto separator = std::make_unique<Separator>();	
	components_.push_back( std::move(separator) );
}

IMenuItem* Menu::createMenuItem(const std::string& label)
{
	auto menuItem = std::make_unique<MenuItem>(label);
	auto menuItemPtr = menuItem.get();
	
	components_.push_back( std::move(menuItem) );
	
	return menuItemPtr;
}

}
}
}
