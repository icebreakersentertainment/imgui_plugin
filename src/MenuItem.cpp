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
	if (ImGui::MenuItem(label_.c_str()))
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

}
}
}
