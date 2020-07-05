#ifndef POPUPMODAL_H_
#define POPUPMODAL_H_

#include "graphics/gui/IPopupModal.hpp"

#include "imgui.h"

#include "Component.hpp"
#include "GenericComponentContainer.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class PopupModal : public GenericComponentContainer, public IPopupModal
{
public:
	PopupModal(const std::string& title = std::string());
	virtual ~PopupModal() final = default;

	virtual void tick(const float32 delta) override final;

	virtual void close() override final;

private:
	void initialize();

	std::string title_;
};

}
}
}

#endif /* POPUPMODAL_H_ */
