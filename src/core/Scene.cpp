#include "Scene.h"

namespace RavenEngine {

Scene::Scene() {
    // Example of adding a node with a unique ID
    static int nextNodeId = 1;
    AddNode(std::make_unique<SceneNode>("InitialNode", nextNodeId++));
}

Scene::~Scene() {
    // Destructor logic
    // No need to manually delete nodes or clear the vector, unique_ptr will handle it
}

void Scene::AddNode(std::unique_ptr<SceneNode> node) {
    entityIDs.insert(node->GetID()); // Add this line
    nodes.push_back(std::move(node));
}

void Scene::RemoveNode(SceneNode* node) {
    entityIDs.erase(node->GetID()); // Add this line
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
        [node](const std::unique_ptr<SceneNode>& unique_ptr) {
            return unique_ptr.get() == node;
        }), nodes.end());
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

std::vector<SceneNode*> Scene::GetAllNodes() const {
    std::vector<SceneNode*> allNodes;
    for (const auto& node : nodes) {
        allNodes.push_back(node.get());
    }
    return allNodes;
}

void Scene::SetParent(SceneNode* child, SceneNode* parent) {
    // Ensure both child and parent are valid
    if (child && parent) {
        // Implement parent-child relationship
        // Update transforms, etc.
    }
}

} // namespace RavenEngine