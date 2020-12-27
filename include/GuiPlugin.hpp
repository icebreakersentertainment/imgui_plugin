#ifndef GUIPLUGIN_H_
#define GUIPLUGIN_H_

#include <memory>
#include <mutex>

#include "IGuiPlugin.hpp"

namespace ice_engine
{

class GuiPlugin : public IGuiPlugin
{
public:
	GuiPlugin() = default;
	~GuiPlugin() override = default;

	std::string getName() const override;

	std::unique_ptr<graphics::gui::IGuiFactory> createFactory() const override;

private:
    mutable std::mutex glewInitializedMutex_;
    mutable bool glewInitialized_ = false;
};

}

#endif /* GUIPLUGIN_H_ */
