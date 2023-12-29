#include "MenuSystem.h"
#include "Doodle.h"
#include "imgui.h"
#include <Windows.h>
#include <iostream>
#define GLFW_EXPOSE_NATIVE_WIN32 // Define this before including glfw3native.h
#include <GLFW/glfw3native.h> // Include the native access header
#include <GLFW/glfw3.h>
#include "DoodleManager.h"

MenuSystem::MenuSystem() {
    //some shit in here constructor implementation i suppose
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

void MenuSystem::createMainMenu(GLFWwindow* window, DoodleManager& doodleManager) {
    static bool openFileClicked = false;

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Project")) {
                // New Project code
            }
            if (ImGui::MenuItem("Open")) {
                openFileClicked = true;
            }
            if (ImGui::MenuItem("Doodle")) {
                doodleManager.CreateNewDoodle(window); // Pass the window argument here
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

std::vector<Doodle>& MenuSystem::getDoodleWindows() {
    return doodleWindows;
}
