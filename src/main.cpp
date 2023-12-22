#include <iostream>
#include "WindowManager.h"
#include "MenuSystem.h"
#include "ImGuiSetup.h"
#include "ResourceManager.h"

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
    ResourceManager::LoadIcon("D:\\RavenEngineProject\\RavenEngine\\Assets\\RavenLogoImgs\\raven16x16.ico", 
                              "D:\\RavenEngineProject\\RavenEngine\\Assets\\RavenLogoImgs\\ravenICO32x32.ico");
    ResourceManager::SetWindowIcons(window);

    // Initialize Dear ImGui context
    ImGuiSetup::Init(window);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Process events
        glfwPollEvents();
        
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
