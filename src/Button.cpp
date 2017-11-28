#include "Button.hpp"

#include "imgui.h"

namespace hercules
{
namespace graphics
{
namespace gui
{

Button::Button(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string& label)
:
	Component::Component(x, y, width, height),
	label_(label),
	callback_([]() {})
{
	initialize();
}

Button::~Button()
{
	
}

void Button::initialize()
{
	
}

void Button::render()
{
	for (auto& component : components_)
	{
		component->render();
	}
}

void Button::tick(const float32 delta)
{
	if (ImGui::Button(label_.c_str()))
	{
		fprintf(stdout, "button pressed\n");
		callback_();
	}
}

void Button::setLabel(const std::string& label)
{
	label_ = label;
}

const std::string& Button::getLabel() const 
{
	return label_;
}

void Button::setCallback(std::function<void()>& callback)
{
	callback_ = callback;
}

}
}
}
