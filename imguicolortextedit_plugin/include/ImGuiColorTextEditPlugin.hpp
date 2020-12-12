#ifndef IMGUICOLORTEXTEDITPLUGIN_H_
#define IMGUICOLORTEXTEDITPLUGIN_H_

#include <memory>

#include "IScriptingEngineBindingPlugin.hpp"

namespace ice_engine
{

class ImGuiColorTextEditPlugin : public IScriptingEngineBindingPlugin
{
public:
	ImGuiColorTextEditPlugin() = default;
	virtual ~ImGuiColorTextEditPlugin() override = default;

	virtual std::string getName() const override;

	virtual std::unique_ptr<IScriptingEngineBindingFactory> createFactory() const override;

};

}

#endif /* IMGUICOLORTEXTEDITPLUGIN_H_ */
