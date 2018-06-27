#ifndef MENUBAR_H_
#define MENUBAR_H_

#include "graphics/gui/IMenuBar.hpp"

#include "Component.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class MenuBar : public Component, public IMenuBar
{
public:
	MenuBar();
	virtual ~MenuBar();

	virtual void tick(const float32 delta) override;
	
	virtual IMenu* createMenu(const std::string& label) override;
	virtual IMenu* getMenu(const std::string& label) const override;
	
private:
	void initialize();
};

}
}
}

#endif /* MENUBAR_H_ */
