#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Utils\MenuSystem.h"
#include "ImGuiManager.h"
#include "Workspace.h"
#include "FileDialog.h"
#include <iostream>

MenuSystem::MenuSystem(Workspace& workspace, GLFWwindow* window)
    : workspace(workspace), mainWindow(window) {
}

void MenuSystem::createMainMenu() {
    if (ImGui::BeginMainMenuBar()) {
        createFileMenu();
        ImGui::EndMainMenuBar();
    }
    handleFileDialog(); // Call this after the main menu bar
}

void MenuSystem::createFileMenu() {
    if (ImGui::BeginMenu("File")) {
        handleFileMenuItems();
        ImGui::EndMenu();
    }
}

void MenuSystem::handleFileMenuItems() {
    if (!fileDialogOpen) { // Only show these items if the file dialog is not open
        if (ImGui::MenuItem("New Project")) {
            std::cout << "New Project selected.\n";
            // New project creation logic here
        }

        if (ImGui::MenuItem("Open")) {
            std::cout << "Open selected. Opening file dialog...\n";
            fileDialogOpen = true; // Set the flag to open the file dialog
        }

        if (ImGui::MenuItem("Save")) {
            std::cout << "Save selected.\n";
            // Save current project logic here
        }

        if (ImGui::MenuItem("Exit")) {
            std::cout << "Exit selected. Closing window...\n";
            glfwSetWindowShouldClose(mainWindow, GLFW_TRUE);
        }
    }
}

void MenuSystem::handleFileDialog() {
    if (fileDialogOpen) {
        std::string filePath = FileDialog::OpenFileDialog(mainWindow);
        if (!filePath.empty()) {
            std::cout << "File selected: " << filePath << std::endl;
            // Handle the file path
            fileDialogOpen = false; // Close the dialog after handling the file
        }
        else {
            std::cout << "File dialog closed without selecting a file." << std::endl;
            // If the dialog was closed without selecting a file
            fileDialogOpen = false;
        }
    }
}