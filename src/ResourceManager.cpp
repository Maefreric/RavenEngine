#include <Windows.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "ResourceManager.h"
#include <iostream>

HICON ResourceManager::smallIcon = nullptr; // Static member variable to store the small icon
HICON ResourceManager::largeIcon = nullptr; // Static member variable to store the large icon

void ResourceManager::LoadIcon(GLFWwindow* window, LPCWSTR iconPath16, LPCWSTR iconPath32) {
    // Load the small icon from the specified file path and store it in the smallIcon variable
    smallIcon = (HICON)LoadImageW(nullptr, iconPath16, IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
    if (smallIcon == nullptr) {
        // Handle the error (e.g., log an error message or throw an exception)
        // You can add your error handling code here
    }
    
    // Load the large icon from the specified file path and store it in the largeIcon variable
    largeIcon = (HICON)LoadImageW(nullptr, iconPath32, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    if (largeIcon == nullptr) {
        // Handle the error (e.g., log an error message or throw an exception)
        // You can add your error handling code here
    }
}

void ResourceManager::SetWindowIcons(GLFWwindow* window) {
    HWND hwnd = glfwGetWin32Window(window); // Get the native Win32 window handle from the GLFW window
    
    // Set the small icon for the window if it exists
    if (smallIcon) {
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)smallIcon);
    }
    
    // Set the large icon for the window if it exists
    if (largeIcon) {
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)largeIcon);
    }
}

void ResourceManager::UnloadIcon() {
    // Destroy the small icon if it exists and set the smallIcon variable to nullptr
    if (smallIcon) {
        DestroyIcon(smallIcon);
        smallIcon = nullptr;
    }
    
    // Destroy the large icon if it exists and set the largeIcon variable to nullptr
    if (largeIcon) {
        DestroyIcon(largeIcon);
        largeIcon = nullptr;
    }
}
