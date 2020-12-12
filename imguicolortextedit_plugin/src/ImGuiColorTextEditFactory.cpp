#include "ImGuiColorTextEditFactory.hpp"

#include "ImGuiColorTextEdit.hpp"

namespace ice_engine
{
namespace imguicolortextedit
{

std::unique_ptr<IScriptingEngineBinding> ImGuiColorTextEditFactory::create(
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
)
{
	std::unique_ptr<IScriptingEngineBinding> ptr = std::make_unique< ImGuiColorTextEdit >(
		properties,
		fileSystem,
		logger,
		graphicsEngine,
		pathfindingEngine,
		physicsEngine,
		scriptingEngine,
		audioEngine,
		networkingEngine,
		gameEngine
	);
	
	return std::move( ptr );
}

}
}
