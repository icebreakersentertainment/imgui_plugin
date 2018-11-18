#ifndef GLMTOIMGUI_H_
#define GLMTOIMGUI_H_

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "imgui.h"

namespace ice_engine
{
namespace graphics
{
namespace gui
{
namespace detail
{

inline ImVec2 toImgui(const glm::vec2& v)
{
	return {v.x, v.y};
}

}
}
}
}

#endif /* GLMTOIMGUI_H_ */
