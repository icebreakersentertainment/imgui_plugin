#ifndef WINDOW_H_
#define WINDOW_H_

#include "graphics/gui/IWindow.hpp"

#include "imgui.h"

#include "Component.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class Window : public Component, public IWindow
{
public:
	Window(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string& title = std::string());
	Window(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const uint32 flags, const std::string& title = std::string());
	virtual ~Window();

	virtual void tick(const float32 delta) override;
	
	virtual ILabel* createLabel(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string label = std::string()) override;
	virtual IButton* createButton(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string label = std::string()) override;
	virtual IMenuBar* createMenuBar() override;
	
	virtual void setTitle(const std::string& title) override;
	virtual const std::string& getTitle() const  override;
    
private:
	void initialize();
	
	uint32 flags_;
	std::string title_;
	
	ImGuiWindowFlags imguiFlags_;
};

}
}
}

#endif /* WINDOW_H_ */
