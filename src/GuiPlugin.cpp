#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT

#include "GuiPlugin.hpp"

#include "GuiFactory.hpp"

namespace ice_engine
{

GuiPlugin::GuiPlugin()
{
}

GuiPlugin::~GuiPlugin()
{
}

std::string GuiPlugin::getName() const
{
	return std::string("imgui");
}

std::unique_ptr<graphics::gui::IGuiFactory> GuiPlugin::createFactory() const
{
	std::unique_ptr<graphics::gui::IGuiFactory> ptr = std::make_unique< graphics::gui::GuiFactory >();
	
	return std::move( ptr );
}

// Exporting `my_namespace::plugin` variable with alias name `plugin`
// (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::plugin, plugin)`)
extern "C" BOOST_SYMBOL_EXPORT GuiPlugin plugin;
GuiPlugin plugin;

}
