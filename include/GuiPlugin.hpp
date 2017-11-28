#ifndef GUIPLUGIN_H_
#define GUIPLUGIN_H_

#include <memory>

#include "IGuiPlugin.hpp"

namespace hercules
{

class GuiPlugin : public IGuiPlugin
{
public:
	GuiPlugin();
	virtual ~GuiPlugin();

	virtual std::string getName() const override;

	virtual std::unique_ptr<graphics::gui::IGuiFactory> createFactory() const override;

};

}

#endif /* GUIPLUGIN_H_ */
