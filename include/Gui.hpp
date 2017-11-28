#ifndef GUI_H_
#define GUI_H_

#include <vector>

#include "graphics/IGraphicsEngine.hpp"
#include "graphics/gui/IGui.hpp"

#include "Component.hpp"
#include "Window.hpp"

#include "graphics/IEventListener.hpp"

#include "utilities/Properties.hpp"
#include "logger/ILogger.hpp"
#include "fs/IFileSystem.hpp"

namespace hercules
{
namespace graphics
{
namespace gui
{

class Gui : public IGui, public graphics::IEventListener
{
public:
	Gui(
		utilities::Properties* properties,
		fs::IFileSystem* fileSystem,
		logger::ILogger* logger,
		IGraphicsEngine* graphicsEngine
	);
	virtual ~Gui();

	virtual void setViewport(const uint32 width, const uint32 height) override;

	virtual void render() override;
	virtual void tick(const float32 delta) override;
	
	virtual IWindow* createWindow(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string title = std::string()) override;
	virtual IWindow* createWindow(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const uint32 flags, const std::string title = std::string()) override;
	
	virtual bool processEvent(const graphics::KeyboardEvent& event) override;
	virtual bool processEvent(const graphics::MouseButtonEvent& event) override;
	virtual bool processEvent(const graphics::MouseMotionEvent& event) override;
	virtual bool processEvent(const graphics::MouseWheelEvent& event) override;
	
	// Implements the IEventListener interface
	virtual bool processEvent(const graphics::Event& event) override;

private:
	utilities::Properties* properties_;
	fs::IFileSystem* fileSystem_;
	logger::ILogger* logger_;
	
	IGraphicsEngine* graphicsEngine_;
	
	std::vector<IComponent*> components_;
	std::vector<std::unique_ptr<IWindow>> windows_;
	
	void initialize();
};

}
}
}

#endif /* GUI_H_ */
