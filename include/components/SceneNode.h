#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../Maths/Vector3.h" // Make sure to include the header file for Vector3

namespace RavenEngine {

class SceneNode {
public:
    SceneNode(const std::string& name, int id); // Add id parameter to constructor
    ~SceneNode();

    void Update(float deltaTime);
    void AddChild(std::unique_ptr<SceneNode> child);
    void RemoveChild(const SceneNode* child);

    const std::string& GetName() const;
    void SetName(const std::string& newName);

    const std::vector<std::unique_ptr<SceneNode>>& GetChildren() const;

    Vector3 GetPosition() const;
    void SetPosition(const Vector3& position);

    Vector3 GetRotation() const;
    void SetRotation(const Vector3& rotation);

    Vector3 GetScale() const;
    void SetScale(const Vector3& scale);

    int GetID() const;

private:
    std::string name;
    std::vector<std::unique_ptr<SceneNode>> children;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    int id; // Unique identifier for each node
};

} // namespace RavenEngine