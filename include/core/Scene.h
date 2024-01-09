#pragma once
#include "SceneNode.h"
#include <vector>
#include <string>
#include <memory> // Include this for std::unique_ptr
#include <set> // Include this for std::set

namespace RavenEngine {

class Scene {
public:
    Scene();
    ~Scene();

    void AddNode(std::unique_ptr<SceneNode> node); // Change this to take a std::unique_ptr<SceneNode>
    void RemoveNode(SceneNode* node);
    void Update(float deltaTime);
    SceneNode* FindNode(const std::string& name) const;
    void SetParent(SceneNode* child, SceneNode* parent);
    const std::vector<std::unique_ptr<SceneNode>>& GetNodes() const; // Change this to return a reference to the vector of std::unique_ptr<SceneNode>
    std::vector<SceneNode*> GetAllNodes() const;

    std::set<int> entityIDs; // Add this line

private:
    std::vector<std::unique_ptr<SceneNode>> nodes; // Change this to std::unique_ptr<SceneNode>
};

} // namespace RavenEngine