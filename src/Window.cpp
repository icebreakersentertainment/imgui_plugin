#include "Window.hpp"

#include "Label.hpp"
#include "Button.hpp"
#include "MenuBar.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

Window::Window(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string& title)
:
	Component::Component(x, y, width, height),
	flags_(0),
	title_(title),
	imguiFlags_(0)
{
	initialize();
}

Window::Window(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const uint32 flags, const std::string& title)
:
	Component::Component(x, y, width, height),
	flags_(flags),
	title_(title),
	imguiFlags_(0)
{
	initialize();
}

Window::~Window()
{
	
}

void Window::initialize()
{
	if (!(flags_ & ICEENGINE_TITLE_BAR))
	{
		imguiFlags_ |= ImGuiWindowFlags_NoTitleBar;
	}
	if (flags_ & ICEENGINE_SHOW_BORDERS)
	{
		imguiFlags_ |= ImGuiWindowFlags_ShowBorders;
	}
	if (!(flags_ & ICEENGINE_MOVABLE))
	{
		imguiFlags_ |= ImGuiWindowFlags_NoMove;
	}
	if (flags_ & ICEENGINE_NO_SCROLLBAR)
	{
		imguiFlags_ |= ImGuiWindowFlags_NoScrollbar;
	}
	/*
	if (!(flags_ & ICEENGINE_CLOSABLE))
	{
		imguiFlags_ |= ImGuiWindowFlags_NoCollapse;
	}
	*/
	if (!(flags_ & ICEENGINE_MINIMIZABLE))
	{
		imguiFlags_ |= ImGuiWindowFlags_NoCollapse;
	}
	if (!(flags_ & ICEENGINE_RESIZABLE))
	{
		imguiFlags_ |= ImGuiWindowFlags_NoResize;
	}
	if (flags_ & ICEENGINE_MENUBAR)
	{
		imguiFlags_ |= ImGuiWindowFlags_MenuBar;
	}
	if (flags_ & ICEENGINE_NO_INPUT)
	{
		imguiFlags_ |= ImGuiWindowFlags_NoInputs;
	}
	
	//imguiFlags_ |= ImGuiWindowFlags_NoSavedSettings;
	
	/*
	ImGuiWindowFlags_NoTitleBar;
    if (!no_border)   window_flags |= ImGuiWindowFlags_ShowBorders;
    if (no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
    if (no_move)      window_flags |= ImGuiWindowFlags_NoMove;
    if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
if (!no_menu) window_flags |= ImGuiWindowFlags_MenuBar;
*/
}

/*
void Window::render()
{
	if (visible_)
	{
		for (auto& component : components_)
		{
			component->render();
		}
	}
}
*/

void Window::tick(const float32 delta)
{
	if (visible_)
	{
		ImGui::SetNextWindowPos(ImVec2(x_, y_), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(width_, height_), ImGuiCond_Always);
		
		if (!ImGui::Begin(title_.c_str(), &visible_, imguiFlags_))
		{
			ImGui::End();
			return;
		}
		
		Component::tick(delta);	
		
		ImGui::End();
	}
}

ILabel* Window::createLabel(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string label)
{
	auto l = std::make_unique<Label>(x, y, width, height, label);
	auto labelPtr = l.get();
	components_.push_back( std::move(l) );
	
	return labelPtr;
}

IButton* Window::createButton(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string label)
{
	auto button = std::make_unique<Button>(x, y, width, height, label);
	auto buttonPtr = button.get();
	components_.push_back( std::move(button) );
	
	return buttonPtr;
}

IMenuBar* Window::createMenuBar()
{
	auto menuBar = std::make_unique<MenuBar>();
	auto menuBarPtr = menuBar.get();
	components_.push_back( std::move(menuBar) );
	
	return menuBarPtr;
}

void Window::setTitle(const std::string& title)
{
	title_ = title;
}

const std::string& Window::getTitle() const 
{
	return title_;
}

}
}
}

