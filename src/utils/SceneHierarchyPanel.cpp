#include "SceneHierarchyPanel.h"
#include <imgui.h>
#include <iostream>

namespace RavenEngine {

SceneHierarchyPanel::SceneHierarchyPanel()
    : context(nullptr), selectedNode(nullptr), nodeToRename(nullptr), renameRequested(false) {}

void SceneHierarchyPanel::SetContext(Scene* newContext) {
    context = newContext;
    selectedNode = nullptr;
    nodeToRename = nullptr;
    renameRequested = false;
}

void SceneHierarchyPanel::OnImGuiRender() {
    ImGui::SetNextWindowSize(ImVec2(300, 600), ImGuiCond_FirstUseEver); // Set default window size
    ImGui::Begin("Scene Hierarchy");

    // Handle input for deleting nodes
    if (selectedNode && ImGui::IsKeyPressed(ImGuiKey_Delete)) {
        context->RemoveNode(selectedNode);
        selectedNode = nullptr;
    }

    if (ImGui::Button("Create Entity")) {
        static int idCounter = 1; // Start from 1 to avoid a zero ID, which ImGui uses as a "null" or "none" ID
        std::string entityName = "New Entity" + std::to_string(idCounter);
        context->AddNode(std::make_unique<SceneNode>(entityName, idCounter++));
    }

    if (context) {
        const auto& nodes = context->GetNodes();
        for (const auto& node : nodes) {
            DrawNodeTree(node.get());
        }
    }

    ImGui::End();
}

void SceneHierarchyPanel::DrawNodeTree(SceneNode* node) {
    ImGuiTreeNodeFlags flags = ((selectedNode == node) ? ImGuiTreeNodeFlags_Selected : 0)
                               | ImGuiTreeNodeFlags_OpenOnArrow
                               | ImGuiTreeNodeFlags_SpanAvailWidth;
    flags |= node->GetChildren().empty() ? ImGuiTreeNodeFlags_Leaf : 0;

    bool treeNodeOpen = ImGui::TreeNodeEx(reinterpret_cast<void*>(static_cast<intptr_t>(node->GetID())), flags, "%s", node->GetName().c_str());

    if (ImGui::IsItemClicked()) {
        selectedNode = node;
    }

    // Context menu
    if (ImGui::BeginPopupContextItem()) {
        if (ImGui::MenuItem("Rename")) {
            nodeToRename = node;
            renameRequested = true;
        }
        // Other context menu items...
        ImGui::EndPopup();
    }

    // Handle in-line renaming
    if (node == nodeToRename && renameRequested) {
        RenderNodeRenaming(node);
    }

    if (treeNodeOpen) {
        for (auto& child : node->GetChildren()) {
            DrawNodeTree(child.get());
        }
        ImGui::TreePop();
    }
}

void SceneHierarchyPanel::RenderNodeRenaming(SceneNode* node) {
    static char buffer[256] = "";
    if (renameRequested) {
        strncpy_s(buffer, sizeof(buffer), node->GetName().c_str(), _TRUNCATE);
        ImGui::SetItemDefaultFocus();
        ImGui::SetKeyboardFocusHere(-1); // Set focus on previous widget
        renameRequested = false;
    }

    if (ImGui::InputText("##edit", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll)) {
        node->SetName(std::string(buffer));
        nodeToRename = nullptr;
    }
    // If the user clicks away from the input box, cancel renaming
    else if (!ImGui::IsItemActive() && !ImGui::IsItemHovered()) {
        nodeToRename = nullptr;
    }
}

void SceneHierarchyPanel::StartRenamingNode(SceneNode* node) {
    // This functionality is now triggered by a double-click or context menu
}

void SceneHierarchyPanel::ApplyRenaming() {
    // This functionality is now handled inline within DrawNodeTree
}

} // namespace RavenEngine