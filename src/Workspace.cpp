#include <iostream>
#include "Workspace.h"
#include <GLFW/glfw3.h>
#include "ComponentCreator.h"  // Make sure to include the ComponentCreator

Workspace::Workspace(int width, int height, int menuBarHeight, GLFWwindow* window) 
    : width(width), height(height), menuBarHeight(menuBarHeight), window(window), componentsManager(*this) {}

bool Workspace::isInside(int x, int y) const {
    return x >= 0 && x < this->width && y >= this->menuBarHeight && y < this->height + this->menuBarHeight;
}

void Workspace::AddComponent(const std::string& componentName) {
    // add component received console debug output
    std::cout << "attempting to add component..." << std::endl;

    // Here you should define the default positions for your new component or pass them as parameters
    int defaultX = 200; // These are placeholder values
    int defaultY = 200; // These are placeholder values
    auto newComponent = ComponentCreator::CreateComponent(componentName, defaultX, defaultY, *this, window);
    if (newComponent) {
        componentsManager.AddComponent(std::move(newComponent));
        // componentmanager.addcomponent sent console debug output
        std::cout << "Component added successfully." << std::endl;
    } else {
        std::cout << "Failed to add component: " << componentName << std::endl;
    }
}

void Workspace::Update() {
    componentsManager.UpdateComponents(); // Assuming you have this method to update components in ComponentsManager
}

void Workspace::Render() {
    glClearColor(0.094f, 0.094f, 0.094f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    componentsManager.RenderComponents(); // Assuming you have this method to render components in ComponentsManager
}
