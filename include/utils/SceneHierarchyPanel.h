#pragma once
#include "scene.h"
#include <vector>

namespace RavenEngine {

class SceneHierarchyPanel {
public:
    SceneHierarchyPanel();
    void SetContext(Scene* context);
    void OnImGuiRender();
    void DrawNodeTree(SceneNode* node);
    void HandleNodeInteraction(SceneNode* node);
    void RemoveNode(SceneNode* node);

    std::vector<SceneNode*> selectedNodes; // Corrected: only one declaration needed

private:
    Scene* context;
    SceneNode* nodeToRename; // Member variable for node to rename
    bool renameRequested; // Flag to indicate renaming is requested
};

} // namespace RavenEngine
