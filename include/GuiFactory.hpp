#ifndef GUIFACTORY_H_
#define GUIFACTORY_H_

#include <memory>

#include "graphics/IGraphicsEngine.hpp"
#include "graphics/gui/IGuiFactory.hpp"

namespace hercules
{
namespace graphics
{
namespace gui
{

class GuiFactory : public IGuiFactory
{
public:
	GuiFactory();
	virtual ~GuiFactory();

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
