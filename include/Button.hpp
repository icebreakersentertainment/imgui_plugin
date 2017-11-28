#ifndef BUTTON_H_
#define BUTTON_H_

#include "graphics/gui/IButton.hpp"

#include "Component.hpp"

namespace hercules
{
namespace graphics
{
namespace gui
{

class Button : public Component, public IButton
{
public:
	Button(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string& label = std::string());
	virtual ~Button();

	virtual void render() override;
	virtual void tick(const float32 delta) override;
	
	virtual void setLabel(const std::string& label) override;
	virtual const std::string& getLabel() const override;
	
	virtual void setCallback(std::function<void()>& callback) override;
    
private:
	void initialize();
	
	std::string label_;
	
	std::function<void()> callback_;
};

}
}
}

#endif /* BUTTON_H_ */
