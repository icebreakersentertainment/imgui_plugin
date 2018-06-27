#ifndef MENU_H_
#define MENU_H_

#include "graphics/gui/IMenu.hpp"

#include "Component.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class Menu : public Component, public IMenu
{
public:
	Menu(const std::string& label = std::string());
	virtual ~Menu();

	virtual void tick(const float32 delta) override;
	
	virtual void setLabel(const std::string& label) override;
	virtual const std::string& getLabel() const  override;
	
	virtual IMenu* createMenu(const std::string& label) override;
	virtual IMenu* getMenu(const std::string& label) const  override;
	
	virtual void createSeparator() override;
	
	virtual IMenuItem* createMenuItem(const std::string& label) override;
	
private:
	void initialize();
	
	std::string label_;
};

}
}
}

#endif /* MENU_H_ */
