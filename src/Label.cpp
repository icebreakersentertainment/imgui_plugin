#include "Label.hpp"

#include "imgui.h"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

Label::Label(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string& label)
:
	Component::Component(x, y, width, height),
	label_(label)
{
	initialize();
}

Label::~Label()
{
	
}

void Label::initialize()
{
	
}

void Label::tick(const float32 delta)
{
	ImGui::Text(label_.c_str());
}

void Label::setLabel(const std::string& label)
{
	label_ = label;
}

const std::string& Label::getLabel() const 
{
	return label_;
}

}
}
}
