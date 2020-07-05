#include <GL/glew.h>

#include <imgui.h>
#include "imgui_impl_sdl_gl3.h"

#include "Gui.hpp"

#include "graphics/Event.hpp"
#include "graphics/Keyboard.hpp"
#include "../../../ice_engine/include/graphics/Event.hpp"
#include "../include/Gui.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

void shutdown(ImGuiData* imGuiData)
{
	ImGui::SetCurrentContext(imGuiData->context);

	ImGui_ImplSdlGL3_Shutdown(imGuiData->sdlData);

	ImGui::DestroyContext(imGuiData->context);
}

Gui::Gui(
	utilities::Properties* properties,
	fs::IFileSystem* fileSystem,
	logger::ILogger* logger,
	IGraphicsEngine* graphicsEngine
)
	:
	properties_(properties),
	fileSystem_(fileSystem),
	logger_(logger),
	imGuiData_(nullptr, shutdown),
	graphicsEngine_(graphicsEngine)
{
	initialize();
}

Gui::~Gui()
{
    LOG_DEBUG(logger_, "Destroying GUI");
	graphicsEngine_->removeEventListener(this);
}

void Gui::initialize()
{
    LOG_DEBUG(logger_, "Initializing GUI");
	imGuiData_ = std::unique_ptr<ImGuiData, void(*)(ImGuiData*)>(new ImGuiData(), shutdown);
	imGuiData_->sdlData = new SdlData();
	//memset(sdlData_, 0, sizeof(SdlData));

	imGuiData_->context = ImGui::CreateContext();

    ImGui::SetCurrentContext(imGuiData_->context);

	ImGui_ImplSdlGL3_Init(imGuiData_->sdlData);

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;

    io.KeyMap[ImGuiKey_Tab] = SCANCODE_TAB;                     // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
    io.KeyMap[ImGuiKey_LeftArrow] = SCANCODE_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = SCANCODE_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = SCANCODE_UP;
    io.KeyMap[ImGuiKey_DownArrow] = SCANCODE_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = SCANCODE_PAGEUP;
    io.KeyMap[ImGuiKey_PageDown] = SCANCODE_PAGEDOWN;
    io.KeyMap[ImGuiKey_Home] = SCANCODE_HOME;
    io.KeyMap[ImGuiKey_End] = SCANCODE_END;
    io.KeyMap[ImGuiKey_Delete] = SCANCODE_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = SCANCODE_BACKSPACE;
    io.KeyMap[ImGuiKey_Enter] = SCANCODE_RETURN;
    io.KeyMap[ImGuiKey_Escape] = SCANCODE_ESCAPE;
    io.KeyMap[ImGuiKey_A] = SCANCODE_A;
    io.KeyMap[ImGuiKey_C] = SCANCODE_C;
    io.KeyMap[ImGuiKey_V] = SCANCODE_V;
    io.KeyMap[ImGuiKey_X] = SCANCODE_X;
    io.KeyMap[ImGuiKey_Y] = SCANCODE_Y;
    io.KeyMap[ImGuiKey_Z] = SCANCODE_Z;

	const glm::uvec2 viewport = graphicsEngine_->getViewport();

	setViewport(viewport.x, viewport.y);

	graphicsEngine_->addEventListener(this);

	ImGui_ImplSdlGL3_NewFrame(imGuiData_->sdlData);
}

void Gui::setViewport(const uint32 width, const uint32 height)
{
	//width_ = width;
	//height_ = height;

	ImGui::SetCurrentContext(imGuiData_->context);

	ImGuiIO& io = ImGui::GetIO();
  io.DisplaySize = ImVec2((float)width, (float)height);
  io.DisplayFramebufferScale = ImVec2(width > 0 ? ((float)width / width) : 0, height > 0 ? ((float)height / height) : 0);
}

void Gui::render()
{
	if (visible())
	{
		ImGui::SetCurrentContext(imGuiData_->context);
		//ImGui_ImplSdlGL3_NewFrame();

		for (auto& component : components_)
		{
			component->render();
		}

		for (auto& window : windows_)
		{
			window->render();
		}

		ImGui::Render();

		auto drawData = ImGui::GetDrawData();
		ImGui_ImplSdlGL3_RenderDrawLists(imGuiData_->sdlData, drawData);
	}
}

void Gui::tick(const float32 delta)
{
	ImGui::SetCurrentContext(imGuiData_->context);

	ImGui_ImplSdlGL3_NewFrame(imGuiData_->sdlData);

	if (mainMenuBar_) mainMenuBar_->tick(delta);

	for (auto& component : components_)
	{
		component->tick(delta);
	}

	for (auto& window : windows_)
	{
		window->tick(delta);
	}
}

bool Gui::visible() const
{
    return visible_;
}

void Gui::setVisible(const bool visible)
{
    visible_ = visible;
}

IWindow* Gui::createWindow(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string title)
{
	auto window = std::make_unique<Window>(x, y, width, height, title);
	windows_.push_back( std::move(window) );

	return windows_.back().get();
}

IWindow* Gui::createWindow(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const uint32 flags, const std::string title)
{
	auto window = std::make_unique<Window>(x, y, width, height, flags, title);
	windows_.push_back( std::move(window) );

	return windows_.back().get();
}

IMainMenuBar* Gui::createMainMenuBar()
{
	if (mainMenuBar_)
	{
		LOG_WARN(logger_, "Main menu bar already exists.")
	}

	mainMenuBar_ = std::make_unique<MainMenuBar>();

	return mainMenuBar_.get();
}

void Gui::destroyMainMenuBar()
{
	mainMenuBar_.reset();
}

IPopupModal* Gui::createPopupModal(const std::string& title)
{
	auto popupModal = std::make_unique<PopupModal>(title);
	auto popupModalPtr = popupModal.get();
	components_.push_back( std::move(popupModal) );

	return popupModalPtr;
}

void Gui::destroy(const IPopupModal* popupModal)
{
	components_.erase(
		std::remove_if(
			components_.begin(),
			components_.end(),
			[popupModal](const std::unique_ptr<IComponent>& c) {
				return c.get() == popupModal;
			}
		),
		components_.end()
	);
}

void Gui::destroy(const IWindow* window)
{
	windows_.erase(
		std::remove_if(
			windows_.begin(),
			windows_.end(),
			[window](const std::unique_ptr<IWindow>& w) {
				return w.get() == window;
			}
		),
		windows_.end()
	);
}

bool Gui::processEvent(const graphics::WindowEvent& event)
{
	return false;
}

bool Gui::processEvent(const graphics::KeyboardEvent& event)
{
	ImGui::SetCurrentContext(imGuiData_->context);

    ImGuiIO& io = ImGui::GetIO();

    const int key = event.keySym.scancode;

    io.KeysDown[key] = (event.type == graphics::KEYDOWN);
    io.KeyShift = event.keySym.mod & graphics::KEYMOD_SHIFT;
    io.KeyCtrl = event.keySym.mod & graphics::KEYMOD_CTRL;
    io.KeyAlt = event.keySym.mod & graphics::KEYMOD_ALT;
    io.KeySuper = event.keySym.mod & graphics::KEYMOD_GUI;

	return ImGui::GetIO().WantCaptureKeyboard || ImGui::GetIO().WantTextInput;
}


bool Gui::processEvent(const graphics::TextInputEvent& event)
{
    ImGui::SetCurrentContext(imGuiData_->context);

    ImGuiIO& io = ImGui::GetIO();

    io.AddInputCharactersUTF8(&event.text[0]);

    return ImGui::GetIO().WantCaptureKeyboard || ImGui::GetIO().WantTextInput;
}

bool Gui::processEvent(const graphics::MouseButtonEvent& event)
{
	ImGui::SetCurrentContext(imGuiData_->context);

	ImGuiIO& io = ImGui::GetIO();

	const int down = (event.state == graphics::KeyState::KEY_PRESSED);

	switch(event.button)
	{
        case graphics::MouseButtonCode::BUTTON_LEFT:
            io.MouseDown[0] = down;
            break;

        case graphics::MouseButtonCode::BUTTON_MIDDLE:
            io.MouseDown[1] = down;
            break;

        case graphics::MouseButtonCode::BUTTON_RIGHT:
            io.MouseDown[2] = down;
            break;

        default:
			break;
	}

	return ImGui::GetIO().WantCaptureMouse;
}

bool Gui::processEvent(const graphics::MouseMotionEvent& event)
{
	ImGui::SetCurrentContext(imGuiData_->context);

	ImGuiIO& io = ImGui::GetIO();

	io.MousePos = ImVec2((float)event.x, (float)event.y);

	return ImGui::GetIO().WantCaptureMouse;
}

bool Gui::processEvent(const graphics::MouseWheelEvent& event)
{
	ImGui::SetCurrentContext(imGuiData_->context);

	ImGuiIO& io = ImGui::GetIO();

	//nk_input_scroll(ctx_, nk_vec2((float)event.x,(float)event.y));
	io.MouseWheel = (event.y > 0 ? 1 : -1);

	return ImGui::GetIO().WantCaptureMouse;
}

bool Gui::processEvent(const graphics::Event& event)
{
	ImGui::SetCurrentContext(imGuiData_->context);

	switch(event.type)
	{
		case graphics::WINDOWEVENT:

			switch(event.window.eventType)
			{
				case graphics::WINDOWEVENT_RESIZED:
					setViewport(event.window.data1, event.window.data2);

				default:
					break;
			}

			return true;
			break;

		default:
			break;
	}

	return false;
}

}
}
}
