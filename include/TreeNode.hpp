#ifndef TREENODE_HPP_
#define TREENODE_HPP_

#include <functional>

#include "graphics/gui/ITreeNode.hpp"

#include "Component.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

class TreeNode : public Component, public ITreeNode
{
public:
    TreeNode(const std::string& label = std::string());
    ~TreeNode() override = default;

    void tick(const float32 delta) override;

    ITreeNode* createNode(const std::string& label) override;
    ITreeNode* getNode(const std::string& label) override;
    void destroy(const ITreeNode* treeNode) override;

    void setLabel(const std::string& label) override;
    const std::string& label() const override;

    void setCallback(std::function<void(ITreeNode*)>& callback);
    void setSelectedCallback(std::function<void(ITreeNode*)> selectedCallback);

    void unselectIfNot(const ITreeNode* treeNode);

private:
    std::string label_;
    bool selected_ = false;
    std::vector<std::unique_ptr<TreeNode>> treeNodes_;
    std::function<void(ITreeNode*)> callback_ = [](ITreeNode*) {};
    std::function<void(ITreeNode*)> selectedCallback_ = [](ITreeNode*) {};
};

}
}
}

#endif //TREENODE_HPP_
