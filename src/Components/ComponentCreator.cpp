#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ComponentCreator.h"
#include "Workspace.h"
#include "TransformComponent.h"

std::unique_ptr<Component> ComponentCreator::CreateComponent(const std::string& type, 
                                                            float x, float y, 
                                                            float width, float height) {
    // Example: creating a TransformComponent, replace with actual logic
    return std::make_unique<TransformComponent>();
}

