// main.cpp
#include "glad/glad.h" 
#include "GLFW/glfw3.h" 
#include <iostream> 
#include "Core\AppWindow.h" 
#include "MenuSystem.h" 
#include "Workspace.h" 
#include "ImGuiManager.h" 
#include "ResourceManager.h" 

int main() { 
    try { 
        // Initialize GLFW and create the main window
        AppWindow appWindow(800, 600, "Raven Engine");
        GLFWwindow* mainWindow = appWindow.getMainWindow();

        // Load and set window icons
        ResourceManager::LoadIcon(mainWindow, L"../Assets/images/icons/raven16x16.ico", 
                                              L"../Assets/images/icons/raven32x32.ico");
        ResourceManager::SetWindowIcons(mainWindow);

        // Initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            throw std::runtime_error("Failed to initialize GLAD");
        }

        // Initialize ImGuiManager for UI handling
        ImGuiManager::Init(mainWindow);

        // Create Workspace and MenuSystem
        Workspace workspace(mainWindow);
        MenuSystem menuSystem(workspace, mainWindow);

        // Main application loop
        while (!appWindow.shouldClose()) {
            // Poll events (keyboard, mouse, etc.)
            appWindow.pollEvents(); 

            // Start UI frame
            ImGuiManager::NewFrame(); 

            // Create dockspace for docking windows
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()); 

            // Create main menu and render workspace
            menuSystem.createMainMenu();
            workspace.Render(); 
            
            // Render UI and swap buffers
            ImGuiManager::Render();
            appWindow.swapBuffers();
        }

        // Shutdown ImGuiManager and unload icons
        ImGuiManager::Shutdown();
        ResourceManager::UnloadIcon();
    } catch (const std::exception& e) {
        // Print any errors and exit with failure status
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Exit with success status
    return EXIT_SUCCESS;
}
// ........................................................................................................................