#include "ComponentsManager.h"
#include "Workspace.h"

ComponentsManager::ComponentsManager(Workspace& workspace) : workspace(workspace) {}

void ComponentsManager::AddComponent(std::unique_ptr<Component> component) {
    components.push_back(std::move(component)); // Add the component to the vector
}

void ComponentsManager::UpdateComponents() {
    for (auto& component : components) {
        component->Update(); // Assuming each component has an Update method
    }
}

void ComponentsManager::RenderComponents() {
    for (auto& component : components) {
        if (component->IsVisible() && workspace.isInside(component->GetX(), component->GetY())) {
            component->Render();
        }
    }
}

void ComponentsManager::RemoveInvisibleComponents() {
    components.erase(
        std::remove_if(components.begin(), components.end(),
                       [](const auto& comp){ return !comp->IsVisible(); }),
        components.end());
}
