#ifndef GUIFACTORY_H_
#define GUIFACTORY_H_

#include <memory>

#include "graphics/IGraphicsEngine.hpp"
#include "graphics/gui/IGuiFactory.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class GuiFactory : public IGuiFactory
{
public:
	virtual std::unique_ptr<IGui> create(
		utilities::Properties* properties,
		fs::IFileSystem* fileSystem,
		logger::ILogger* logger,
		IGraphicsEngine* graphicsEngine
	) override;

};

}
}
}

#endif /* GUIFACTORY_H_ */
