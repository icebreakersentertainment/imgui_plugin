#ifndef GENERICCOMPONENTCONTAINER_H_
#define GENERICCOMPONENTCONTAINER_H_

#include <imgui/imgui.h>

#include "graphics/gui/IGenericComponentContainer.hpp"

#include "imguicolortextedit/ITextEditor.hpp"
#include "imguicolortextedit/ITextEditorFactory.hpp"

#include "Component.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class GenericComponentContainer : public Component, public ITextEditorFactory, public virtual IGenericComponentContainer
{
public:
	GenericComponentContainer() = default;
	GenericComponentContainer(const uint32 x, const uint32 y, const uint32 width, const uint32 height);
	virtual ~GenericComponentContainer() override = default;

	virtual ILabel* createLabel(const std::string label = std::string()) override;
	virtual ILabel* createLabel(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string label = std::string()) override;
	virtual IButton* createButton(const std::string label = std::string()) override;
	virtual IButton* createButton(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string label = std::string()) override;
    virtual ITextField* createTextField(const std::string text = std::string()) override;
    virtual ITextField* createTextField(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string text = std::string()) override;
    virtual ITextArea* createTextArea(const std::string text = std::string()) override;
    virtual ITextArea* createTextArea(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string text = std::string()) override;
    virtual ITreeView* createTreeView() override;
    virtual IComboBox* createComboBox() override;

    ITextEditor* createTextEditor(const std::string text = std::string()) override;
    ITextEditor* createTextEditor(const uint32 x, const uint32 y, const uint32 width, const uint32 height, const std::string text = std::string()) override;

    void add(std::unique_ptr<IComponent> component) override;


    virtual void destroy(const ILabel* label) override;
	virtual void destroy(const IButton* button) override;
	virtual void destroy(const ITextField* textField) override;
	virtual void destroy(const ITextArea* textArea) override;
	virtual void destroy(const ITreeView* treeView) override;
	virtual void destroy(const IComboBox* comboBox) override;

    std::unique_ptr<IComponent> remove(const IComponent* component) override;

private:
	void initialize();
};

}
}
}

#endif /* GENERICCOMPONENTCONTAINER_H_ */
