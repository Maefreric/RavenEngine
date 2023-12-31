// Defines
#define GLFW_EXPOSE_NATIVE_WIN32
// Includes
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Windows.h>
#include <iostream>

// Project includes
#include "imgui.h"
#include "MenuSystem.h"
#include "Workspace.h"

MenuSystem::MenuSystem(Workspace& workspace) : workspace(workspace) {
    // Constructor implementation...
}

bool MenuSystem::OpenFileDialog(char* selectedFile, int bufferSize, GLFWwindow* ownerWindow) {
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);

    // Use GLFW to get the native window handle
    HWND hwndOwner = glfwGetWin32Window(ownerWindow);
    ofn.hwndOwner = hwndOwner;
    
    ofn.lpstrFile = selectedFile;
    ofn.lpstrFile[0] = '\0'; // Ensure the first character is null
    ofn.nMaxFile = bufferSize;
    ofn.lpstrFilter = "All Files\0*.*\0";
    ofn.lpstrTitle = "Open File";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn)) {
        // File selected successfully
        return true;
    } else {
        // Check for errors and handle them
        DWORD error = CommDlgExtendedError();
        if (error != 0) {
            std::cout << "File dialog error: " << error << std::endl;
        }
        return false;
    }
}

void MenuSystem::createMainMenu(GLFWwindow* window) {
    static bool openFileClicked = false;

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Project")) {
                // New Project code
            }

            // +Component menu
            // lists all current available components (might want to in the future set this up to be dynamic)
            if (ImGui::BeginMenu("+Component")) {
                if (ImGui::MenuItem("Doodle")) {
                    workspace.AddComponent("Doodle");  // Add a Doodle component to the workspace
                    // console output for debugging
                    std::cout << "workspace.addcomponent sent" << std::endl;
                }
                // Add more components as needed
                ImGui::EndMenu();
            }

            if (ImGui::MenuItem("Open")) {
                openFileClicked = true;
            }
            if (ImGui::MenuItem("Save")) {
                // Save code
            }
            if (ImGui::MenuItem("Exit")) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    // Get the height of the main menu bar
    float MENU_BAR_HEIGHT = ImGui::GetFrameHeight();

    // Outside of any ImGui::Begin/End calls
    if (openFileClicked) {
        char selectedFile[MAX_PATH];
        ZeroMemory(selectedFile, sizeof(selectedFile)); // Ensure buffer is initialized
        if (OpenFileDialog(selectedFile, MAX_PATH, window)) {
            std::cout << "Selected file: " << selectedFile << std::endl;
        } else {
            // User canceled or error occurred
        }
        openFileClicked = false; // Reset the flag after handling file dialog
    }
}