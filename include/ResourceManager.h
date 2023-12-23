#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <GLFW/glfw3.h>
#include <Windows.h> // Include Windows.h here to ensure HICON is recognized

class ResourceManager {
public:
    /**
     * @brief Loads the window icons from the specified file paths.
     * 
     * @param window The GLFW window to set the icons for.
     * @param iconPath16 The file path of the 16x16 icon.
     * @param iconPath32 The file path of the 32x32 icon.
     */
    static void LoadIcon(GLFWwindow* window, LPCWSTR iconPath16, LPCWSTR iconPath32);

    /**
     * @brief Sets the loaded window icons for the specified GLFW window.
     * 
     * This function should be called after calling LoadIcon.
     * 
     * @param window The GLFW window to set the icons for.
     */
    static void SetWindowIcons(GLFWwindow* window);

    /**
     * @brief Unloads the loaded window icons.
     * 
     * This function should be called when the icons are no longer needed.
     */
    static void UnloadIcon();

private:
    static HICON smallIcon; // The handle to the small icon
    static HICON largeIcon; // The handle to the large icon
};

#endif // RESOURCE_MANAGER_H
