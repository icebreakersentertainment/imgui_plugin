#include "MainMenuBar.hpp"

#include "imgui.h"

#include "Menu.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

MainMenuBar::MainMenuBar()
{
	initialize();
}

MainMenuBar::~MainMenuBar()
{

}

void MainMenuBar::initialize()
{

}

void MainMenuBar::tick(const float32 delta)
{
	if (ImGui::BeginMainMenuBar())
	{
		for (auto& c : components_)
		{
			c->tick(delta);
		}

		ImGui::EndMainMenuBar();
	}
}

IMenu* MainMenuBar::createMenu(const std::string& label)
{
	auto menu = std::make_unique<Menu>(label);
	auto menuPtr = menu.get();

	components_.push_back( std::move(menu) );

	return menuPtr;
}

IMenu* MainMenuBar::getMenu(const std::string& label) const
{
	return nullptr;
}

}
}
}
