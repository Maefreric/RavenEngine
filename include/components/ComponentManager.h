#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <memory>
#include <vector>
#include "Component.h"

class ComponentManager {
private:
    std::vector<std::unique_ptr<Component>> components;

public:
    ComponentManager();
    void AddComponent(std::unique_ptr<Component> component);

    void UpdateComponents(); // Calls Update on all components
    void RenderImGuiComponents(); // Calls RenderImGui on all components
};

#endif // COMPONENT_MANAGER_H