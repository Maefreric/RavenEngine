#include "SceneHierarchyPanel.h"
#include <imgui.h>
#include <iostream>

namespace RavenEngine {

SceneHierarchyPanel::SceneHierarchyPanel()
    : context(nullptr), nodeToRename(nullptr), renameRequested(false) {}

void SceneHierarchyPanel::SetContext(Scene* newContext) {
    context = newContext;
    selectedNodes.clear(); // Clear the selection
    nodeToRename = nullptr;
    renameRequested = false;
}

void SceneHierarchyPanel::OnImGuiRender() {
    ImGui::SetNextWindowSize(ImVec2(300, 600), ImGuiCond_FirstUseEver);
    ImGui::Begin("Scene Hierarchy");

    // Handle deletion of multiple selected nodes
    if (!selectedNodes.empty() && ImGui::IsKeyPressed(ImGuiKey_Delete)) {
        for (auto& selectedNode : selectedNodes) {
            context->RemoveNode(selectedNode);
        }
        selectedNodes.clear();
    }

    if (ImGui::Button("Create Entity")) {
        int newID = context->entityIDs.empty() ? 1 : *context->entityIDs.rbegin() + 1; // Check if entityIDs is empty
        std::string entityName = "New Entity" + std::to_string(newID);
        auto newNode = std::make_unique<SceneNode>(entityName, newID);
        context->AddNode(std::move(newNode));
        std::cout << "Created new entity: " << entityName << std::endl;
    }

    if (context) {
        for (auto& node : context->GetNodes()) {
            DrawNodeTree(node.get());
        }
    }

    // Handle renaming
    if (renameRequested && nodeToRename) {
        ImGui::OpenPopup("Rename Node");
        renameRequested = false;
    }

    if (ImGui::BeginPopupModal("Rename Node", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        static char buffer[256];
        if (nodeToRename) {
            strncpy_s(buffer, sizeof(buffer), nodeToRename->GetName().c_str(), _TRUNCATE);
            ImGui::SetKeyboardFocusHere(); // Auto focus on text input
            if (ImGui::InputText("##edit", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
                nodeToRename->SetName(std::string(buffer));
                nodeToRename = nullptr;
            }
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}

void SceneHierarchyPanel::DrawNodeTree(SceneNode* node) {
    if (!node) {
        std::cerr << "Attempted to draw a null SceneNode." << std::endl;
        return;
    }

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
    if (node->GetChildren().empty()) {
        flags |= ImGuiTreeNodeFlags_Leaf;
    }

    // Check if the current node is one of the selected nodes
    if (std::find(selectedNodes.begin(), selectedNodes.end(), node) != selectedNodes.end()) {
        flags |= ImGuiTreeNodeFlags_Selected;
    }

    ImGui::PushID(node->GetID());
    bool treeNodeOpen = ImGui::TreeNodeEx(node->GetName().c_str(), flags);

    HandleNodeInteraction(node);

    if (treeNodeOpen) {
        for (auto& child : node->GetChildren()) {
            DrawNodeTree(child.get());
        }
        ImGui::TreePop();
    }
    ImGui::PopID();
}


void SceneHierarchyPanel::HandleNodeInteraction(SceneNode* node) {
    bool ctrlPressed = ImGui::GetIO().KeyCtrl;
    bool shiftPressed = ImGui::GetIO().KeyShift;

    if (ImGui::IsItemClicked()) {
        // Multi-selection with Ctrl key
        if (ctrlPressed) {
            auto it = std::find(selectedNodes.begin(), selectedNodes.end(), node);
            if (it == selectedNodes.end()) {
                selectedNodes.push_back(node); // Add to selection if not already selected
            } else {
                selectedNodes.erase(it); // Remove from selection if already selected
            }
        } else if (shiftPressed) {
            // Range selection with Shift key
            std::vector<SceneNode*> allNodes = context->GetAllNodes();
            if (selectedNodes.empty()) {
                selectedNodes.push_back(node); // If no nodes are selected, select the current node
            } else {
                // Find the first selected node and the current node in the allNodes list
                auto firstSelectedNodeIt = std::find(allNodes.begin(), allNodes.end(), selectedNodes.front());
                auto currentNodeIt = std::find(allNodes.begin(), allNodes.end(), node);

                // Select all nodes between the first selected node and the current node
                selectedNodes.clear();
                for (auto it = std::min(firstSelectedNodeIt, currentNodeIt); it != std::max(firstSelectedNodeIt, currentNodeIt) + 1; ++it) {
                    selectedNodes.push_back(*it);
                }
            }
        } else {
            // Regular selection (single node)
            selectedNodes.clear();
            selectedNodes.push_back(node);
        }
    }

    if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) { // 0 is the left mouse button
        nodeToRename = node;
        renameRequested = true;
    }

    if (ImGui::BeginPopupContextItem()) {
        if (ImGui::MenuItem("Rename")) {
            nodeToRename = node;
            renameRequested = true;
        }
        if (ImGui::MenuItem("Delete")) {
            // Check if the node is in the selectedNodes list
            auto it = std::find(selectedNodes.begin(), selectedNodes.end(), node);
            if (it != selectedNodes.end()) {
                // Node is selected, delete all selected nodes
                for (auto& selectedNode : selectedNodes) {
                    context->RemoveNode(selectedNode);
                }
                selectedNodes.clear();
            } else {
                // Node is not selected, delete only this node
                context->RemoveNode(node);
            }
        }
        ImGui::EndPopup();
    }

    // Handle renaming logic
    if (nodeToRename == node && renameRequested) {
        ImGui::OpenPopup("RenameNode");
        nodeToRename = nullptr;
        renameRequested = false;
    }

    if (ImGui::BeginPopup("RenameNode")) {
        static char buffer[256] = "";
        if (buffer[0] == '\0') { // Is the buffer empty? (First time we open the popup)
            strncpy_s(buffer, sizeof(buffer), node->GetName().c_str(), _TRUNCATE);
            ImGui::SetKeyboardFocusHere(); // Auto focus on text input
        }
        if (ImGui::InputText("##edit", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
            node->SetName(std::string(buffer));
            buffer[0] = '\0'; // Clear the buffer
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

} // namespace RavenEngine
