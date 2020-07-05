#ifndef MENUITEM_H_
#define MENUITEM_H_

#include "graphics/gui/IMenuItem.hpp"

#include "Component.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class MenuItem : public Component, public IMenuItem
{
public:
	MenuItem(const std::string& label = std::string());
	virtual ~MenuItem();

	virtual void tick(const float32 delta) override;

	virtual void setLabel(const std::string& label) override;
	virtual const std::string& getLabel() const  override;

	virtual void setCallback(std::function<void()>& callback) override;

	virtual IMenuItem* createMenuItem(const std::string& label) override;

private:
	void initialize();

	std::string label_;

	std::function<void()> callback_;
};

}
}
}

#endif /* MENUITEM_H_ */
