#include <imgui/imgui.h>

#include "Label.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

Label::Label(const std::string& label) : label_(label)
{
	initialize();
}

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
    ImGui::PushID(uuid_.c_str());

	ImGui::Text(label_.c_str());

    ImGui::PopID();
}

void Label::setLabel(const std::string& label)
{
	label_ = label;
}

const std::string& Label::label() const
{
	return label_;
}

}
}
}
