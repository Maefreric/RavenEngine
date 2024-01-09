#include "Scene.h"

namespace RavenEngine {

Scene::Scene() {
    // Constructor logic
}

Scene::~Scene() {
    // Destructor logic
    // No need to manually delete nodes or clear the vector, unique_ptr will handle it
}

void Scene::AddNode(std::unique_ptr<SceneNode> node) {
    if (node) {
        nodes.push_back(std::move(node)); // Use std::move to transfer ownership
        // Initialize node or any other setup if needed
    }
}

void Scene::RemoveNode(SceneNode* node) {
    auto it = std::find_if(nodes.begin(), nodes.end(),
                           [node](const std::unique_ptr<SceneNode>& n) { return n.get() == node; });
    if (it != nodes.end()) {
        // Additional logic before deleting, if needed
        nodes.erase(it); // unique_ptr will handle deletion
    }
}

void Scene::Update(float deltaTime) {
    for (auto& node : nodes) { // Use reference to avoid copying unique_ptr
        if (node) {
            node->Update(deltaTime);
        }
    }
}

SceneNode* Scene::FindNode(const std::string& name) const {
    for (const auto& node : nodes) { // Use const reference to avoid copying unique_ptr
        if (node && node->GetName() == name) {
            return node.get();
        }
    }
    return nullptr;
}

const std::vector<std::unique_ptr<SceneNode>>& Scene::GetNodes() const {
    return nodes;
}

void Scene::SetParent(SceneNode* child, SceneNode* parent) {
    // Ensure both child and parent are valid
    if (child && parent) {
        // Implement parent-child relationship
        // Update transforms, etc.
    }
}

} // namespace RavenEngine