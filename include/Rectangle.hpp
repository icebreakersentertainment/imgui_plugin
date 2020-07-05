#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "graphics/gui/IRectangle.hpp"

#include "Component.hpp"

#include "detail/GlmToImgui.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class Rectangle : public Component, public IRectangle
{
public:
	Rectangle() = default;
	Rectangle(const glm::vec2& start, const glm::vec2& end, const Color& color) : start_(start), end_(end), color_(color)
	{
	}

	virtual ~Rectangle() final = default;

	virtual void tick(const float32 delta) final
	{
		ImGui::GetWindowDrawList()->AddRect(detail::toImgui(start_), detail::toImgui(end_), color_.color());
	}

	virtual void setPoints(const glm::vec2& start, const glm::vec2& end) final
	{
		start_ = start;
		end_ = end;
	}

	virtual const glm::vec2& getStartPoint() const final
	{
				return start_;
	}

	virtual const glm::vec2& getEndPoint() const  final
	{
		return end_;
	}

	virtual void setColor(const Color& color) final
	{
		color_ = color;
	}

	virtual const Color& getColor() const  final
	{
		return color_;
	}

private:
	glm::vec2 start_;
	glm::vec2 end_;
	Color color_;
};

}
}
}

#endif /* RECTANGLE_H_ */
