#include <algorithm>
#include <iostream>

#include <imgui/imgui.h>

#include "TreeNode.hpp"

namespace ice_engine
{
namespace graphics
{
namespace gui
{

TreeNode::TreeNode(const std::string& label) : label_(label)
{

}

void TreeNode::tick(const float32 delta)
{
    ImGui::PushID(uuid_.c_str());

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_None;
    if (treeNodes_.empty()) flags |= ImGuiTreeNodeFlags_Leaf;
    if (selected_) flags |= ImGuiTreeNodeFlags_Selected;

    if (ImGui::TreeNodeEx(label_.c_str(), flags))
    {
        if (ImGui::IsItemClicked())
        {
            selected_ = true;
            selectedCallback_(this);
            callback_(this);
        }

        for (const auto& node : treeNodes_)
        {
            node->tick(delta);
        }

        ImGui::TreePop();
    }
    else if (selected_)
    {
        selected_ = false;
    }

    ImGui::PopID();
}

ITreeNode* TreeNode::createNode(const std::string& label)
{
    auto treeNode = std::make_unique<TreeNode>(label);
    auto treeNodePtr = treeNode.get();

    treeNode->setCallback(callback_);
    treeNode->setSelectedCallback(selectedCallback_);

    treeNodes_.push_back( std::move(treeNode) );

    return treeNodePtr;
}

ITreeNode* TreeNode::getNode(const std::string& label)
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

void TreeNode::destroy(const ITreeNode* treeNode)
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

void TreeNode::setLabel(const std::string& label)
{
    label_ = label;
}

const std::string& TreeNode::label() const
{
    return label_;
}

void TreeNode::setCallback(std::function<void(ITreeNode*)>& callback)
{
    callback_ = callback;

    for (const auto& node : treeNodes_)
    {
        node->setCallback(callback);
    }
}

void TreeNode::setSelectedCallback(std::function<void(ITreeNode*)> selectedCallback)
{
    selectedCallback_ = selectedCallback;

    for (const auto& node : treeNodes_)
    {
        node->setSelectedCallback(selectedCallback);
    }
}

void TreeNode::unselectIfNot(const ITreeNode* treeNode)
{
    if (this != treeNode) selected_ = false;

    for (const auto& node : treeNodes_)
    {
        node->unselectIfNot(treeNode);
    }
}

}
}
}