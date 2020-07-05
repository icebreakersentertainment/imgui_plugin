#include "PopupModal.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

PopupModal::PopupModal(const std::string& title)
:
	title_(title)
{
	initialize();
}

void PopupModal::initialize()
{

}

void PopupModal::tick(const float32 delta)
{
	if (visible_) ImGui::OpenPopup(title_.c_str());

	if (ImGui::BeginPopupModal(title_.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		Component::tick(delta);
	}
}

void PopupModal::close()
{
	if (visible_) ImGui::CloseCurrentPopup();

	visible_ = false;
}

}
}
}
