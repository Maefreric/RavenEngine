// workspace.cpp
#include "Workspace.h"
#include <iostream>
#include <algorithm>
#include <GLFW/glfw3.h>
#include "ComponentCreator.h"
#include "imgui_internal.h"

bool Workspace::printedMenuData = false;

Workspace::Workspace(float width, float height, float menuBarHeight, GLFWwindow* mainWin, WindowManager& wm)
    : width(width), height(height), menuBarHeight(menuBarHeight), window(mainWin), componentsManager(*this), windowManager(wm) {
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;  // Disable .ini file saving/loading for window positions and sizes
}

void Workspace::AddComponent(const std::string& componentName) {
    std::cout << "workspace.AddComponent received: " << componentName << std::endl;

    // Component window creation logic
    int componentWindowWidth = 200;
    int componentWindowHeight = 200;
    GLFWwindow* componentWindow = windowManager.createWindow(componentWindowWidth, componentWindowHeight, componentName.c_str(), true, componentName);

    if (!componentWindow) {
        std::cerr << "Failed to create window for component: " << componentName << std::endl;
        return;
    }

    // Define initial x, y, width, and height for the component
    int clampedX = 0;
    int clampedY = 0;
    int initialComponentWidth = 100;
    int initialComponentHeight = 100;

    // Here, pass componentWindow instead of 'window' to the ComponentCreator
    auto newComponent = ComponentCreator::CreateComponent(
        componentName, clampedX, clampedY, initialComponentWidth, initialComponentHeight, *this, componentWindow
    );

    // Check if the component was created successfully
    if (newComponent) {
        componentsManager.AddComponent(std::move(newComponent));
        std::cout << "Component added" << std::endl;
    } else {
        std::cerr << "Failed to create component: " << componentName << std::endl;
        windowManager.destroyComponentWindow(componentName); // Destroy the window if component creation failed
    }
}

void Workspace::Update() {
    componentsManager.UpdateComponents();
}

void Workspace::Render() {
    glClearColor(0.094f, 0.094f, 0.094f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    componentsManager.UpdateComponents();  // Make sure components are updated
    componentsManager.RenderComponents();  // Render components within bounds
}

void Workspace::SetSize(float newWidth, float newHeight) {
    // Implementation of SetSize
}

std::pair<float, float> Workspace::ClampPosition(float x, float y) const {
    // Implementation of ClampPosition
}

ImVec2 Workspace::ClampPositionInBounds(float x, float y, float windowWidth, float windowHeight) const {
    // Implementation of ClampPositionInBounds
}

void Workspace::SetCurrentCursor(GLFWcursor* cursor) {
    // Implementation of SetCurrentCursor
}