#ifndef WINDOW_H_
#define WINDOW_H_

#include <imgui/imgui.h>

#include "graphics/gui/IWindow.hpp"

#include "Component.hpp"
#include "GenericComponentContainer.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class Window : public GenericComponentContainer, public IWindow
{
public:
	Window(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string& title = std::string());
	Window(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const uint32 flags, const std::string& title = std::string());

	virtual void tick(const float32 delta) override;

	virtual IMenuBar* createMenuBar() override;
	virtual IRectangle* createRectangle(const glm::vec2& start, const glm::vec2& end, const Color& color) override final;

	virtual void destroy(const IRectangle* rectangle) override final;

	virtual void setTitle(const std::string& title) override;
	virtual const std::string& title() const override;

	virtual void setBackgroundAlpha(const float32 alpha) override final
	{
		alpha_ = alpha;
	}

private:
	void initialize();

	uint32 flags_;
	std::string title_;

	float32 alpha_ = 1.0f;

	ImGuiWindowFlags imguiFlags_;
};

}
}
}

#endif /* WINDOW_H_ */
