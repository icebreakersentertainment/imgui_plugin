#ifndef TREEVIEW_HPP_
#define TREEVIEW_HPP_

#include <vector>
#include <memory>

#include "graphics/gui/ITreeView.hpp"

#include "Component.hpp"
#include "TreeNode.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class TreeView : public Component, public ITreeView
{
public:
    TreeView();

    ~TreeView() override = default;

    void tick(const float32 delta) override;

    ITreeNode* createNode(const std::string& label) override;
    ITreeNode* getNode(const std::string& label) override;
    void destroy(const ITreeNode* treeNode) override;

    void select(ITreeNode* treeNode) override;
    void unselect(const ITreeNode* treeNode) override;
    bool selected(const ITreeNode* treeNode) const override;

    void setCallback(std::function<void(ITreeNode*)>& callback) override;
    void selectedCallback(const ITreeNode* treeNode);

private:
    std::function<void(ITreeNode*)> callback_ = [](ITreeNode*) {};
    std::vector<std::unique_ptr<TreeNode>> treeNodes_;
    ITreeNode* selected_ = nullptr;

};

}
}
}


#endif //TREEVIEW_HPP_
