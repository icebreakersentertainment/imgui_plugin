#ifndef LABEL_H_
#define LABEL_H_

#include "graphics/gui/ILabel.hpp"

#include "Component.hpp"

namespace hercules
{
namespace graphics
{
namespace gui
{

class Label : public Component, public ILabel
{
public:
	Label(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string& label = std::string());
	virtual ~Label();

	virtual void render() override;
	virtual void tick(const float32 delta) override;
	
	virtual void setLabel(const std::string& label) override;
	virtual const std::string& getLabel() const override;
	
private:
	void initialize();
	
	std::string label_;
};

}
}
}

#endif /* LABEL_H_ */
