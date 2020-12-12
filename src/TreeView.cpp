#include <algorithm>
#include <iostream>

#include <imgui/imgui.h>

#include "TreeView.hpp"

#include "TreeNode.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

TreeView::TreeView()
{

}

void TreeView::tick(const float32 delta)
{
    ImGui::PushID(uuid_.c_str());

    for (const auto& node : treeNodes_)
    {
        node->tick(delta);
    }

    ImGui::PopID();
}

ITreeNode* TreeView::createNode(const std::string& label)
{
    auto treeNode = std::make_unique<TreeNode>(label);
    auto treeNodePtr = treeNode.get();

    treeNode->setCallback(callback_);
    treeNode->setSelectedCallback([this](ITreeNode* treeNode) { this->selectedCallback(treeNode); });

    treeNodes_.push_back( std::move(treeNode) );

    return treeNodePtr;
}

ITreeNode* TreeView::getNode(const std::string& label)
{
    auto func = [&label](const auto& n) {
        return n->label() == label;
    };

    auto it = std::find_if(treeNodes_.begin(), treeNodes_.end(), func);

    if (it != treeNodes_.end())
    {
        return it->get();
    }

    return nullptr;
}

void TreeView::destroy(const ITreeNode* treeNode)
{
    auto func = [treeNode](const auto& cbi) {
        return cbi.get() == treeNode;
    };

    auto it = std::find_if(treeNodes_.begin(), treeNodes_.end(), func);

    if (it != treeNodes_.end())
    {
        treeNodes_.erase(it);
    }
}

void TreeView::select(ITreeNode* treeNode)
{

}

void TreeView::unselect(const ITreeNode* treeNode)
{

}

bool TreeView::selected(const ITreeNode* treeNode) const
{
    return false;
}

void TreeView::setCallback(std::function<void(ITreeNode*)>& callback)
{
    callback_ = callback;

    for (const auto& node : treeNodes_)
    {
        node->setCallback(callback);
    }
}

void TreeView::selectedCallback(const ITreeNode* treeNode)
{
    for (const auto& node : treeNodes_)
    {
        node->unselectIfNot(treeNode);
    }
}

}
}
}