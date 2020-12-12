#ifndef IMGUICOLORTEXTEDIT_H_
#define IMGUICOLORTEXTEDIT_H_

#include <vector>

#include "IScriptingEngineBindingPlugin.hpp"

#include "utilities/Properties.hpp"
#include "logger/ILogger.hpp"
#include "fs/IFileSystem.hpp"

namespace ice_engine
{

namespace scripting
{
class IScriptingEngine;
}
namespace networking
{
class INetworkingEngine;
}
namespace graphics
{
class IGraphicsEngine;
namespace gui
{
class IWindow;
class ITextEditor;
}
}
namespace pathfinding
{
class IPathfindingEngine;
}
namespace physics
{
class IPhysicsEngine;
}
namespace audio
{
class IAudioEngine;
}
namespace logger
{
class ILogger;
}

class GameEngine;

namespace imguicolortextedit
{

class ImGuiColorTextEdit : public IScriptingEngineBinding
{
public:
	ImGuiColorTextEdit(
		utilities::Properties* properties,
		fs::IFileSystem* fileSystem,
		logger::ILogger* logger,
		graphics::IGraphicsEngine* graphicsEngine,
		pathfinding::IPathfindingEngine* pathfindingEngine,
		physics::IPhysicsEngine* physicsEngine,
		scripting::IScriptingEngine* scriptingEngine,
		audio::IAudioEngine* audioEngine,
		networking::INetworkingEngine* networkingEngine,
		GameEngine* gameEngine
	);

	virtual void bind() override;
	
private:
	logger::ILogger* logger_;
	GameEngine* gameEngine_;
	scripting::IScriptingEngine* scriptingEngine_;

    graphics::gui::ITextEditor* createTextEditor(graphics::gui::IWindow* window, const std::string text = std::string());
    graphics::gui::ITextEditor* createTextEditor(graphics::gui::IWindow* window, const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string text = std::string());
};

}
}

#endif /* IMGUICOLORTEXTEDIT_H_ */

