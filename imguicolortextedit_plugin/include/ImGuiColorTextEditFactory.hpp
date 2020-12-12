#ifndef IMGUICOLORTEXTEDITFACTORY_H_
#define IMGUICOLORTEXTEDITFACTORY_H_

#include <memory>

#include "IScriptingEngineBindingFactory.hpp"

namespace ice_engine
{
namespace imguicolortextedit
{

class ImGuiColorTextEditFactory : public IScriptingEngineBindingFactory
{
public:
	ImGuiColorTextEditFactory() = default;
	virtual ~ImGuiColorTextEditFactory() override = default;

	virtual std::unique_ptr<IScriptingEngineBinding> create(
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
	) override;

};

}
}

#endif /* IMGUICOLORTEXTEDITFACTORY_H_ */
