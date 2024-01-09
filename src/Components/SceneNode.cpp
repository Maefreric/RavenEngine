#include "SceneNode.h"
#include <iostream>

namespace RavenEngine {

SceneNode::SceneNode(const std::string& name, int id)
    : name(name), id(id), position(Vector3()), rotation(Vector3()), scale(Vector3(1.0f, 1.0f, 1.0f)) {
    // Constructor initializes components, transform, etc.
}

SceneNode::~SceneNode() {
    // Destructor logic should handle cleanup of components, child nodes, and other resources
}

void SceneNode::Update(float deltaTime) {
    // Update the node's components, transform, etc.

    // Update child nodes
    for (auto& child : children) {
        child->Update(deltaTime);
    }
}


void SceneNode::AddChild(std::unique_ptr<SceneNode> child) {
    children.push_back(std::move(child));
}

void SceneNode::RemoveChild(const SceneNode* child) {
    children.erase(std::remove_if(children.begin(), children.end(),
                                  [child](const std::unique_ptr<SceneNode>& c) { return c.get() == child; }),
                   children.end());
}

const std::string& SceneNode::GetName() const {
    return name;
}

void SceneNode::SetName(const std::string& newName) {
    std::cout << "SetName called. New name: " << newName << std::endl; // Debug print
    name = newName;
}

const std::vector<std::unique_ptr<SceneNode>>& SceneNode::GetChildren() const {
    return children;
}

Vector3 SceneNode::GetPosition() const {
    return position;
}

void SceneNode::SetPosition(const Vector3& newPosition) {
    position = newPosition;
}

Vector3 SceneNode::GetRotation() const {
    return rotation;
}

void SceneNode::SetRotation(const Vector3& newRotation) {
    rotation = newRotation;
}

Vector3 SceneNode::GetScale() const {
    return scale;
}

void SceneNode::SetScale(const Vector3& newScale) {
    scale = newScale;
}

int SceneNode::GetID() const {
    return id;
}

// Implement additional methods for components and transformations here.

} // namespace RavenEngine