// Main.cpp
// Standard library headers
#include <iostream>

// Third-party library headers
#include "imgui.h"

// Raven headers
#include "ImGuiSetup.h"
#include "MenuSystem.h"
#include "ResourceManager.h"
#include "WindowManager.h"
#include "Workspace.h"

int main() {
    // Initialize WindowManager and create window
    WindowManager windowManager;
    GLFWwindow* window = windowManager.createWindow(800, 600, "Raven Engine");
    windowManager.setWindowProperties(window);
    ResourceManager::LoadIcon(window, L"../src/Assets/raven16x16.ico", L"../src/Assets/raven32x32.ico");
    ResourceManager::SetWindowIcons(window);
    ImGuiSetup::Init(window);

    // Create Workspace instance
    int widthInt, heightInt;
    glfwGetFramebufferSize(window, &widthInt, &heightInt);
    float width = static_cast<float>(widthInt);
    float height = static_cast<float>(heightInt);
    float menuBarHeight = ImGui::GetFrameHeight();
    Workspace workspace(width, height - menuBarHeight, menuBarHeight, window, windowManager);

    MenuSystem menuSystem(workspace);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGuiSetup::NewFrame();
        
        menuSystem.createMainMenu(window);
        workspace.Update(); // Update all components
        workspace.Render(); // Render workspace and all components

        ImGuiSetup::Render();
        glfwSwapBuffers(window);
    }

    ImGuiSetup::Shutdown();
    ResourceManager::UnloadIcon();
    windowManager.cleanUp();

    return 0;
}