#include "ComponentManager.h"
#include "../../include/core/Workspace.h"
#include <iostream>

ComponentManager::ComponentManager(Workspace& workspace) : workspace(workspace) {}

void ComponentManager::AddComponent(std::unique_ptr<Component> component) {
    components.push_back(std::move(component)); // Add the component to the vector
}

void ComponentManager::UpdateComponents() {
    for (auto& component : components) {
        if (!component->IsVisible()) {
            continue; // Skip non-visible components
        }

        if (!workspace.isInside(component->GetX(), component->GetY())) {
            continue; // Skip components outside workspace bounds
        }
        component->Update();
        component->PreRender();
        component->Render();
        component->PostRender();
    }
}

void ComponentManager::RenderComponents() {
    for (auto& component : components) {
        if (component->IsVisible() && workspace.isInside(component->GetX(), component->GetY())) {
            component->Render();
        }
    }
}

void ComponentManager::RemoveInvisibleComponents() {
    components.erase(
        std::remove_if(components.begin(), components.end(),
                       [](const auto& comp){ return !comp->IsVisible(); }),
        components.end());
}

size_t ComponentManager::GetComponentCount() const {
    return components.size();
}