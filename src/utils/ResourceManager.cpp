#include <Windows.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "ResourceManager.h"
#include <iostream>

HICON ResourceManager::smallIcon = nullptr;
HICON ResourceManager::largeIcon = nullptr;

void ResourceManager::LoadIcon(GLFWwindow* window, LPCWSTR iconPath16, LPCWSTR iconPath32) {
    // Use absolute paths for debugging purposes
    // You should see the correct absolute path printed in the console
    wchar_t fullIconPath16[MAX_PATH];
    wchar_t fullIconPath32[MAX_PATH];
    GetFullPathNameW(iconPath16, MAX_PATH, fullIconPath16, nullptr);
    GetFullPathNameW(iconPath32, MAX_PATH, fullIconPath32, nullptr);

    std::wcerr << L"Attempting to load small icon from: " << fullIconPath16 << std::endl;
    std::wcerr << L"Attempting to load large icon from: " << fullIconPath32 << std::endl;

    smallIcon = (HICON)LoadImageW(NULL, fullIconPath16, IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
    if (smallIcon == nullptr) {
        std::cerr << "Failed to load small icon. Error: " << GetLastError() << std::endl;
    }

    largeIcon = (HICON)LoadImageW(NULL, fullIconPath32, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    if (largeIcon == nullptr) {
        std::cerr << "Failed to load large icon. Error: " << GetLastError() << std::endl;
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

void ResourceManager::SetWindowIcons(GLFWwindow* window) {
    // Get the HWND from the GLFWwindow* using glfwGetWin32Window
    HWND hwnd = glfwGetWin32Window(window);

    // Set the small icon for the window using the HWND and the smallIcon variable
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)smallIcon);

    // Set the large icon for the window using the HWND and the largeIcon variable
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)largeIcon);
}