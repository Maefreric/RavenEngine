#ifndef COMPONENTSMANAGER_H
#define COMPONENTSMANAGER_H

#include <vector>
#include <memory> // For std::unique_ptr
#include "Components.h" // Make sure this is the correct include for your Component class

class Workspace; // Forward declaration

class ComponentsManager {
public:
    ComponentsManager(Workspace& workspace);
    ~ComponentsManager() = default;

    void AddComponent(std::unique_ptr<Component> component);
    void UpdateComponents();
    void RenderComponents();
    void RemoveInvisibleComponents(); // Added this line
    void ClampAndRenderComponents(); // Added this line
    size_t GetComponentCount() const;

private:
    std::vector<std::unique_ptr<Component>> components;
    Workspace& workspace;
};

#endif // COMPONENTSMANAGER_H