#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"
#include <glm/glm.hpp>

class TransformComponent : public Component {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    TransformComponent();
    void Update() override;
    void RenderImGui() override;
    glm::mat4 GetTransformMatrix() const;
    void Translate(const glm::vec3& delta);
    void Rotate(const glm::vec3& delta);
    void Scale(const glm::vec3& delta);
};

#endif // TRANSFORM_COMPONENT_H