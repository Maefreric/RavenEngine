#include <iostream>
#include "WindowManager.h"
#include "MenuSystem.h"
#include "ImGuiSetup.h"
#include "ResourceManager.h"
#include "imgui.h"

int main() {
    // Create an instance of WindowManager
    WindowManager windowManager;
    
    // Create an instance of MenuSystem
    MenuSystem menuSystem;
    
    // Create a GLFW window using the WindowManager
    GLFWwindow* window = windowManager.createWindow(800, 600, "Raven Engine");
    
    // Set properties of the GLFW window
    windowManager.setWindowProperties(window);
    
    // Load and set window icons using the ResourceManager
    ResourceManager::LoadIcon(
        window,
        L"D:\\RavenEngineProject\\RavenEngine\\Assets\\RavenLogoImgs\\raven16x16.ico",
        L"D:\\RavenEngineProject\\RavenEngine\\Assets\\RavenLogoImgs\\raven32x32.ico"
    );
    
    ResourceManager::SetWindowIcons(window);

    // Initialize Dear ImGui context
    ImGuiSetup::Init(window);

    while (!glfwWindowShouldClose(window)) {
        // Process events
        glfwPollEvents();
        
        // Clear the screen
        glClearColor(24.0f / 255.0f, 24.0f / 255.0f, 24.0f / 255.0f, 1.0f); // Set clear color to a dark gray
        glClear(GL_COLOR_BUFFER_BIT); // Clear the buffer to the set color

        // Start a new Dear ImGui frame
        ImGuiSetup::NewFrame();

        // Create the main menu using the MenuSystem
        menuSystem.createMainMenu(window);

        // Render Dear ImGui
        ImGuiSetup::Render();
        
        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Clean up Dear ImGui, ResourceManager, and WindowManager
    ImGuiSetup::Shutdown();
    ResourceManager::UnloadIcon();
    windowManager.cleanUp(window);

    return 0;
}
