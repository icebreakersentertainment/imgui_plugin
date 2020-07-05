#ifndef MAINMENUBAR_H_
#define MAINMENUBAR_H_

#include "graphics/gui/IMainMenuBar.hpp"

#include "Component.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class MainMenuBar : public Component, public IMainMenuBar
{
public:
	MainMenuBar();
	virtual ~MainMenuBar();

	virtual void tick(const float32 delta) override;

	virtual IMenu* createMenu(const std::string& label) override;
	virtual IMenu* getMenu(const std::string& label) const override;

private:
	void initialize();
};

}
}
}

#endif /* MAINMENUBAR_H_ */
