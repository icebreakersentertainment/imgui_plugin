#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT

#include "ImGuiColorTextEditPlugin.hpp"

#include "ImGuiColorTextEditFactory.hpp"

namespace ice_engine
{

std::string ImGuiColorTextEditPlugin::getName() const
{
	return std::string("imguicolortextedit");
}

std::unique_ptr<IScriptingEngineBindingFactory> ImGuiColorTextEditPlugin::createFactory() const
{
	std::unique_ptr<IScriptingEngineBindingFactory> ptr = std::make_unique< imguicolortextedit::ImGuiColorTextEditFactory >();
	
	return std::move( ptr );
}

// Exporting `my_namespace::plugin` variable with alias name `plugin`
// (Has the same effect as `BOOST_DLL_ALIAS(my_namespace::plugin, plugin)`)
extern "C" BOOST_SYMBOL_EXPORT ImGuiColorTextEditPlugin plugin;
ImGuiColorTextEditPlugin plugin;

}
