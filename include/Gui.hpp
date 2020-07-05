#ifndef GUI_H_
#define GUI_H_

#include <vector>
#include <memory>

#include "graphics/IGraphicsEngine.hpp"
#include "graphics/gui/IGui.hpp"

#include "Component.hpp"
#include "Window.hpp"
#include "MainMenuBar.hpp"
#include "PopupModal.hpp"

#include "graphics/IEventListener.hpp"

#include "utilities/Properties.hpp"
#include "logger/ILogger.hpp"
#include "fs/IFileSystem.hpp"

class ImGuiContext;
class SdlData;

namespace ice_engine
{
namespace graphics
{
namespace gui
{

struct ImGuiData
{
	ImGuiContext* context = nullptr;
	SdlData* sdlData = nullptr;
};

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

    virtual bool visible() const override;
    virtual void setVisible(const bool visible) override;

	virtual void setStyle(const Style& style) final
	{
		style_ = style;
		// TODO: set the global style
	}

	virtual const Style& getStyle() const final
	{
		return style_;
	}

	virtual IWindow* createWindow(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string title = std::string()) override;
	virtual IWindow* createWindow(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const uint32 flags, const std::string title = std::string()) override;

	virtual IMainMenuBar* createMainMenuBar() override;
	virtual void destroyMainMenuBar() override;

	virtual IPopupModal* createPopupModal(const std::string& title) override;
	virtual void destroy(const IPopupModal* popupModal) override;
	virtual void destroy(const IWindow* window) override;

	virtual bool processEvent(const graphics::WindowEvent& event) override;
	virtual bool processEvent(const graphics::KeyboardEvent& event) override;
	virtual bool processEvent(const graphics::TextInputEvent& event) override;
	virtual bool processEvent(const graphics::MouseButtonEvent& event) override;
	virtual bool processEvent(const graphics::MouseMotionEvent& event) override;
	virtual bool processEvent(const graphics::MouseWheelEvent& event) override;

	// Implements the IEventListener interface
	virtual bool processEvent(const graphics::Event& event) override;

private:
	utilities::Properties* properties_;
	fs::IFileSystem* fileSystem_;
	logger::ILogger* logger_;

    bool visible_ = true;

	IGraphicsEngine* graphicsEngine_;

	std::unique_ptr<ImGuiData, void(*)(ImGuiData*)> imGuiData_;

	std::vector<std::unique_ptr<IComponent>> components_;
	std::vector<std::unique_ptr<IWindow>> windows_;
	std::unique_ptr<IMainMenuBar> mainMenuBar_;

	Style style_;

	void initialize();
};

}
}
}

#endif /* GUI_H_ */
