#include <GL/glew.h>

#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT

#include "GuiPlugin.hpp"

#include "GuiFactory.hpp"

namespace ice_engine
{

std::string GuiPlugin::getName() const
{
	return std::string("imgui");
}

std::unique_ptr<graphics::gui::IGuiFactory> GuiPlugin::createFactory() const
{
    {
        std::lock_guard<std::mutex> lockGuard(glewInitializedMutex_);
        if (!glewInitialized_) {
            // We need to initialize glew within the imgui plugin
            glewExperimental = GL_TRUE; // Needed in core profile

            const GLenum glewErr = glewInit();

            if (glewErr != GLEW_OK) {
                std::stringstream ss;
                ss << "Failed to initialize GLEW: " << glewGetErrorString(glewErr);
                throw std::runtime_error(ss.str());
            }

            glewInitialized_ = true;
        }
    }

	std::unique_ptr<graphics::gui::IGuiFactory> ptr = std::make_unique< graphics::gui::GuiFactory >();
	
	return std::move( ptr );
}

// Exporting `my_namespace::plugin` variable with alias name `plugin`
// (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::plugin, plugin)`)
extern "C" BOOST_SYMBOL_EXPORT GuiPlugin plugin;
GuiPlugin plugin;

}
