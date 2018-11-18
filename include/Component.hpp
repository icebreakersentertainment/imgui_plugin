#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <vector>
#include <memory>

#include "graphics/gui/IComponent.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class Component : public virtual IComponent
{
public:
	Component() = default;
	Component(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const bool visible = true);
	//virtual ~Component();

	virtual void render() override;
	virtual void tick(const float32 delta) override;
	
	virtual void setStyle(const Style& style) override
			{
				style_ = style;
				customStyle_ = true;
			}

	virtual const Style& getStyle() const override
			{
				return style_;
			}

	virtual void setPosition(const uint32 x, const uint32 y) override;
	virtual glm::ivec2 getPosition() const override;
	
	virtual void setDimensions(const uint32 width, const uint32 height) override;
	virtual glm::ivec2 getDimensions() const  override;
	
	virtual void addComponent(IComponent* component) override;
	virtual void removeComponent(IComponent* component) override;
	virtual void removeAllComponents() override;
	
protected:
	virtual ~Component() = default;
	
	uint32 x_ = 0;
	uint32 y_ = 0;
	uint32 width_ = 0;
	uint32 height_ = 0;
	bool visible_ = true;
	
	Style style_;
	bool customStyle_ = false;

	std::vector<std::unique_ptr<IComponent>> components_;
	
private:

	void initialize();

};

}
}
}

#endif /* COMPONENT_H_ */
