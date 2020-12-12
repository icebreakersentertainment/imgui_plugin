#include <algorithm>

#include <imgui/imgui.h>

#include "Component.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

Component::Component(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const bool visible)
:
	x_(x),
	y_(y),
	width_(width),
	height_(height),
	visible_(visible)
{
	initialize();
}

void Component::initialize()
{

}

void Component::render()
{
	for (auto& component : components_)
	{
		component->render();
	}
}

void Component::tick(const float32 delta)
{
	for (auto& component : components_)
	{
		component->tick(delta);
	}

	repositioned_ = false;
	resized_ = false;
}

void Component::setPosition(const uint32 x, const uint32 y)
{
	x_ = x;
	y_ = y;
	repositioned_ = true;
}

glm::ivec2 Component::position() const
{
	return glm::ivec2(x_, y_);
}

void Component::setDimensions(const uint32 width, const uint32 height)
{
	width_ = width;
	height_ = height;
	resized_ = true;
}

glm::ivec2 Component::dimensions() const
{
	return glm::ivec2(width_, height_);
}

void Component::addComponent(IComponent* component)
{
	//components_.push_back(component);
}

void Component::removeComponent(IComponent* component)
{
	auto func = [component](const auto& comp) {
		return comp.get() == component;
	};

	auto it = std::find_if(components_.begin(), components_.end(), func);

	if (it != components_.end())
	{
		components_.erase(it);
	}
}

void Component::removeAllComponents()
{
	components_.clear();
}

}
}
}
