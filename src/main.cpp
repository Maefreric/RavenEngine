#include <iostream>
#include "WindowManager.h"
#include "MenuSystem.h"
#include "ImGuiSetup.h"
#include "ResourceManager.h"
#include "imgui.h"
#include "Doodle.h"
#include "DoodleManager.h"

void RenderDoodles(std::vector<Doodle*>& doodles) {
    for (auto& doodle : doodles) {
        if (doodle->IsWindowShown()) {
            doodle->Render();
        }
    }

    // Remove closed doodles
    doodles.erase(std::remove_if(doodles.begin(), doodles.end(), 
        [](Doodle* d) { 
            bool shouldRemove = !d->IsWindowShown();
            if (shouldRemove) {
                delete d;  // Ensure to delete the Doodle instance
            }
            return shouldRemove;
        }), doodles.end());
}

int main() {
    // Create an instance of WindowManager
    WindowManager windowManager;
    
    // Create an instance of MenuSystem
    MenuSystem menuSystem;

    DoodleManager doodleManager;
    
    // Create a GLFW window using the WindowManager
    GLFWwindow* window = windowManager.createWindow(800, 600, "Raven Engine");
    
    // Set properties of the GLFW window
    windowManager.setWindowProperties(window);
    
    ResourceManager::LoadIcon(
        window,
        L"../src/Assets/raven16x16.ico",
        L"../src/Assets/raven32x32.ico"
    );
    
    ResourceManager::SetWindowIcons(window);

    // Initialize Dear ImGui context
    ImGuiSetup::Init(window);

    // Main loop
    while (!glfwWindowShouldClose(window)) {

        // Process events
        glfwPollEvents();
        
        // Clear the screen
        glClearColor(24.0f / 255.0f, 24.0f / 255.0f, 24.0f / 255.0f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT); 

        // Start a new Dear ImGui frame
        ImGuiSetup::NewFrame();

        // Create the main menu using the MenuSystem
        menuSystem.createMainMenu(window, doodleManager); 

        // Render doodles
        doodleManager.RenderDoodles(); // Only this call is needed

        // Render Dear ImGui
        ImGuiSetup::Render();
        
        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Clean up
    ImGuiSetup::Shutdown();
    ResourceManager::UnloadIcon();
    windowManager.cleanUp(window);

    return 0;
}