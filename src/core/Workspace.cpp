#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Workspace.h"
#include <iostream>
#include "ComponentCreator.h"
#include "imgui_internal.h"

Workspace::Workspace(GLFWwindow* mainWin)
    : window(mainWin), componentManager(), viewport(window), sceneHierarchyPanel(), currentScene() {
    std::cout << "Initializing Workspace..." << std::endl;
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr; // Disable .ini file saving/loading

    console.AddLog("Workspace initialized successfully.");

    sceneHierarchyPanel.SetContext(&currentScene); // Set the current scene in the panel
}

void Workspace::AddComponent(const std::string& componentName) {
    std::cout << "Adding component: " << componentName << std::endl;
    float initialComponentWidth = 100.0f;
    float initialComponentHeight = 100.0f;

    auto newComponent = ComponentCreator::CreateComponent(
        componentName, 0.0f, 0.0f, initialComponentWidth, initialComponentHeight
    );

    if (newComponent) {
        componentManager.AddComponent(std::move(newComponent));
        std::cout << "Component added successfully." << std::endl;
    } else {
        std::cerr << "Failed to create component: " << componentName << std::endl;
    }
}

void Workspace::Update() {
    componentManager.UpdateComponents();
    // Update other components as needed, such as the current scene
}

void Workspace::Render() {
    glClearColor(0.094f, 0.094f, 0.094f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    componentManager.RenderImGuiComponents();

    viewport.Render();

    sceneHierarchyPanel.OnImGuiRender(); // Render the scene hierarchy panel

    bool consoleWindowOpen = true; // Or manage this state as needed
    console.Draw("Console", &consoleWindowOpen); // Add this line

    glDisable(GL_BLEND);
}

bool Workspace::isInside(float x, float y) const {
    std::cout << "Checking if point (" << x << ", " << y << ") is inside the workspace..." << std::endl;
    // Implement the logic to check if the point (x, y) is inside the workspace
    // For now, returning true as placeholder
    return true;
}