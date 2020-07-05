#include "Button.hpp"

#include "imgui.h"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

Button::Button(const std::string& label) : label_(label)
{
	initialize();
}

Button::Button(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string& label)
:
	Component::Component(x, y, width, height),
	label_(label)
{
	initialize();
}

Button::~Button()
{

}

void Button::initialize()
{

}

void Button::tick(const float32 delta)
{
	if (ImGui::Button(label_.c_str()))
	{
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
