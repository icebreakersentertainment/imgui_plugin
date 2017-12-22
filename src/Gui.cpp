#include <GL/glew.h>

#include <imgui.h>
#include "imgui_impl_sdl_gl3.h"

#include "Gui.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

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
	graphicsEngine_(graphicsEngine)
{
	initialize();
}

Gui::~Gui()
{
	ImGui_ImplSdlGL3_Shutdown();
	
	graphicsEngine_->removeEventListener(this);
}

void Gui::initialize()
{
	ImGui_ImplSdlGL3_Init();
	
	const glm::uvec2 viewport = graphicsEngine_->getViewport();

	setViewport(viewport.x, viewport.y);
	
	graphicsEngine_->addEventListener(this);
}

void Gui::setViewport(const uint32 width, const uint32 height)
{
	//width_ = width;
	//height_ = height;
	
	ImGuiIO& io = ImGui::GetIO();
	
    io.DisplaySize = ImVec2((float)width, (float)height);
    io.DisplayFramebufferScale = ImVec2(width > 0 ? ((float)width / width) : 0, height > 0 ? ((float)height / height) : 0);
}

void Gui::render()
{
	//ImGui_ImplSdlGL3_NewFrame();
	
	for (auto component : components_)
	{
		component->render();
	}
	
	for (auto& window : windows_)
	{
		window->render();
	}
	
	ImGui::Render();
}

void Gui::tick(const float32 delta)
{
	ImGui_ImplSdlGL3_NewFrame();
	
	for (auto component : components_)
	{
		component->tick(delta);
	}
	
	for (auto& window : windows_)
	{
		window->tick(delta);
	}
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

bool Gui::processEvent(const graphics::KeyboardEvent& event)
{
	int down = (event.state == graphics::KeyState::KEY_PRESSED);
	//const Uint8* state = 0;//SDL_GetKeyboardState(0);
	//SDL_Keycode sym = evt->key.keysym.sym;
	switch(event.keySym.scancode)
	{
        case graphics::SCANCODE_RSHIFT:
        case graphics::SCANCODE_LSHIFT:
            //nk_input_key(ctx_, NK_KEY_SHIFT, down);
            break;
            
        case graphics::SCANCODE_DELETE:
            //nk_input_key(ctx_, NK_KEY_DEL, down);
            break;
            
        case graphics::SCANCODE_RETURN:
            //nk_input_key(ctx_, NK_KEY_ENTER, down);
            break;
            
        case graphics::SCANCODE_TAB:
            //nk_input_key(ctx_, NK_KEY_TAB, down);
            break;
            
        case graphics::SCANCODE_BACKSPACE:
            //nk_input_key(ctx_, NK_KEY_BACKSPACE, down);
			break;
			
        case graphics::SCANCODE_HOME:
            //nk_input_key(ctx_, NK_KEY_TEXT_START, down);
            //nk_input_key(ctx_, NK_KEY_SCROLL_START, down);
			break;
			
        case graphics::SCANCODE_END:
            //nk_input_key(ctx_, NK_KEY_TEXT_END, down);
            //nk_input_key(ctx_, NK_KEY_SCROLL_END, down);
			break;
			
        case graphics::SCANCODE_PAGEDOWN:
            //nk_input_key(ctx_, NK_KEY_SCROLL_DOWN, down);
			break;
			
        case graphics::SCANCODE_PAGEUP:
            //nk_input_key(ctx_, NK_KEY_SCROLL_UP, down);
			break;
			
        case graphics::SCANCODE_Z:
            //nk_input_key(ctx_, NK_KEY_TEXT_UNDO, down && (event.keySym.mod & KEYMOD_CTRL));
			break;
			
        case graphics::SCANCODE_R:
            //nk_input_key(ctx_, NK_KEY_TEXT_REDO, down && (event.keySym.mod & KEYMOD_CTRL));
			break;
			
        case graphics::SCANCODE_C:
            //nk_input_key(ctx_, NK_KEY_COPY, down && (event.keySym.mod & KEYMOD_CTRL));
			break;
			
        case graphics::SCANCODE_V:
            //nk_input_key(ctx_, NK_KEY_PASTE, down && (event.keySym.mod & KEYMOD_CTRL));
			break;
			
        case graphics::SCANCODE_X:
            //nk_input_key(ctx_, NK_KEY_CUT, down && (event.keySym.mod & KEYMOD_CTRL));
			break;
			
        case graphics::SCANCODE_B:
            //nk_input_key(ctx_, NK_KEY_TEXT_LINE_START, down && (event.keySym.mod & KEYMOD_CTRL));
			break;
			
        case graphics::SCANCODE_E:
            //nk_input_key(ctx_, NK_KEY_TEXT_LINE_END, down && (event.keySym.mod & KEYMOD_CTRL));
			break;
			
        case graphics::SCANCODE_UP:
            //nk_input_key(ctx_, NK_KEY_UP, down);
			break;
			
        case graphics::SCANCODE_DOWN:
            //nk_input_key(ctx_, NK_KEY_DOWN, down);
			break;
			
        case graphics::SCANCODE_LEFT:
            if (event.keySym.mod & KEYMOD_CTRL)
            {
                //nk_input_key(ctx_, NK_KEY_TEXT_WORD_LEFT, down);
            }
            else
            {
				//nk_input_key(ctx_, NK_KEY_LEFT, down);
			}
			break;
			
        case graphics::SCANCODE_RIGHT:
            if (event.keySym.mod & KEYMOD_CTRL)
            {
                //nk_input_key(ctx_, NK_KEY_TEXT_WORD_RIGHT, down);
			}
			else
			{
				//nk_input_key(ctx_, NK_KEY_RIGHT, down);
			}
			break;
		
		default:
			break;
    }
	
	return false;
}

bool Gui::processEvent(const graphics::MouseButtonEvent& event)
{
	ImGuiIO& io = ImGui::GetIO();
	
	int down = (event.state == graphics::KeyState::KEY_PRESSED);
	const int x = event.x;
	const int y = event.y;
	
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
	
	return false;
}

bool Gui::processEvent(const graphics::MouseMotionEvent& event)
{
	ImGuiIO& io = ImGui::GetIO();
	
	io.MousePos = ImVec2((float)event.x, (float)event.y);
	
	return false;
}

bool Gui::processEvent(const graphics::MouseWheelEvent& event)
{
	ImGuiIO& io = ImGui::GetIO();
	
	//nk_input_scroll(ctx_, nk_vec2((float)event.x,(float)event.y));
	io.MouseWheel = (event.y > 0 ? 1 : -1);
	
	return false;
}

bool Gui::processEvent(const graphics::Event& event)
{
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
