#include "Separator.hpp"

#include "imgui.h"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

Separator::Separator()
{
	initialize();
}

Separator::~Separator()
{
	
}

void Separator::initialize()
{
	
}

void Separator::tick(const float32 delta)
{
	ImGui::Separator();
}

}
}
}
