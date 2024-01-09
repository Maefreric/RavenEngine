#include "TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

TransformComponent::TransformComponent() 
    : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f) {}

void TransformComponent::Update() {
    // Update logic for the transform component
}

void TransformComponent::RenderImGui() {
    // ImGui rendering for transform component properties
    ImGui::SliderFloat3("Position", &position.x, -100.0f, 100.0f);
    ImGui::SliderFloat3("Rotation", &rotation.x, -180.0f, 180.0f);
    ImGui::SliderFloat3("Scale", &scale.x, 0.1f, 10.0f);
}

glm::mat4 TransformComponent::GetTransformMatrix() const {
    glm::mat4 posMatrix = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 rotXMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
    glm::mat4 rotYMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
    glm::mat4 rotZMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

    glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;
    return posMatrix * rotMatrix * scaleMatrix;
}

void TransformComponent::Translate(const glm::vec3& delta) {
    position += delta;
}

void TransformComponent::Rotate(const glm::vec3& delta) {
    rotation += delta;
    // Normalize or adjust rotation values if necessary
}

void TransformComponent::Scale(const glm::vec3& delta) {
    scale *= delta;
}