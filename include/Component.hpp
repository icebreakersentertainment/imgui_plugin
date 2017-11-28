#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <vector>
#include <memory>

#include "graphics/gui/IComponent.hpp"

namespace hercules
{
namespace graphics
{
namespace gui
{

class Component : public virtual IComponent
{
public:
	Component(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const bool visible = true);
	virtual ~Component();

	virtual void render() override;
	virtual void tick(const float32 delta) override;
	
	virtual void setPosition(const uint32 x, const uint32 y) override;
	virtual glm::ivec2 getPosition() const override;
	
	virtual void setDimensions(const uint32 width, const uint32 height) override;
	virtual glm::ivec2 getDimensions() const  override;
	
	virtual void addComponent(IComponent* component) override;
	virtual void removeComponent(IComponent* component) override;
	virtual void removeAllComponents() override;
	
protected:
	uint32 x_;
	uint32 y_;
	uint32 width_;
	uint32 height_;
	bool visible_;
	
	std::vector<std::unique_ptr<IComponent>> components_;
	
private:
	void initialize();
};

}
}
}

#endif /* COMPONENT_H_ */
