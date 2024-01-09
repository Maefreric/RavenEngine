// ComponentManager.cpp
#include "ComponentManager.h"

ComponentManager::ComponentManager() {
    // Initialize your ComponentManager object here if needed
}

void ComponentManager::AddComponent(std::unique_ptr<Component> component) {
    components.push_back(std::move(component));
}

void ComponentManager::UpdateComponents() {
    for (auto& component : components) {
        if (component->IsVisible()) {
            component->Update();
        }
    }
}

void ComponentManager::RenderImGuiComponents() {
    for (auto& component : components) {
        if (component->IsVisible()) {
            component->RenderImGui();
        }
    }
}