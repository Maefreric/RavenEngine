#include "MenuSystem.h"
#include "imgui.h"

MenuSystem::MenuSystem() {
    // Constructor logic if necessary
}

void MenuSystem::createMainMenu(GLFWwindow* window) {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            // File dropdown options
            if (ImGui::MenuItem("New Project")) {
                // TODO: Implement New Project
            }
            if (ImGui::MenuItem("Open")) {
                // TODO: Implement open functionality
            }
            if (ImGui::MenuItem("Save")) {
                // TODO: Implement save functionality
            }
            if (ImGui::MenuItem("Exit")) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
            ImGui::EndMenu();
        }
        // Other menus can be added here later
        ImGui::EndMainMenuBar();
    }
}
