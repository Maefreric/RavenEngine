#pragma once
#include "scene.h"
#include <unordered_set> // Include for storing a set of nodes to delete

namespace RavenEngine {

class SceneHierarchyPanel {
public:
    SceneHierarchyPanel();
    void SetContext(Scene* context);
    void OnImGuiRender();

    // Function to recursively render scene nodes in a tree view
    void DrawNodeTree(SceneNode* node);

    // Removes a node from the scene
    void RemoveNode(SceneNode* node);

    // Update the declaration of RenderNodeRenaming
    void RenderNodeRenaming(SceneNode* node);

    void StartRenamingNode(SceneNode* node);
    void ApplyRenaming();

private:
    Scene* context;
    SceneNode* selectedNode; // Member variable for selected node
    SceneNode* nodeToRename; // Member variable for node to rename
    bool renameRequested; // Flag to indicate renaming is requested

    // Stores nodes to delete after ImGui frame to avoid iterator invalidation
    std::unordered_set<SceneNode*> nodesToDelete; 
};

} // namespace RavenEngine