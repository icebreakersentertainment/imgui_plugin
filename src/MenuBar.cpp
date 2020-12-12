#include <imgui/imgui.h>

#include "MenuBar.hpp"

#include "Menu.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

MenuBar::MenuBar()
{
	initialize();
}

MenuBar::~MenuBar()
{
	
}

void MenuBar::initialize()
{
	
}

void MenuBar::tick(const float32 delta)
{
	if (ImGui::BeginMenuBar())
	{
		for (auto& c : components_)
		{
			c->tick(delta);
		}
		
		ImGui::EndMenuBar();
	}
}

IMenu* MenuBar::createMenu(const std::string& label)
{
	auto menu = std::make_unique<Menu>(label);	
	auto menuPtr = menu.get();
	
	components_.push_back( std::move(menu) );
	
	return menuPtr;
}

IMenu* MenuBar::getMenu(const std::string& label) const
{
	return nullptr;
}

}
}
}
