#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <GLFW/glfw3.h>
#include <string>
#include <memory>
#include <utility> // Include for std::pair
#include "ComponentsManager.h" // Include ComponentsManager
#include "imgui.h" // Include for ImVec2
#include "WindowManager.h" // Include WindowManager

class Workspace {
private:
    float width;
    float height;
    float menuBarHeight;
    GLFWwindow* window;
    ComponentsManager componentsManager;
    WindowManager& windowManager;
    static bool printedMenuData;

    // Private methods (if any) go here

public:
    // Constructor
    Workspace(float width, float height, float menuBarHeight, GLFWwindow* window, WindowManager& wm);

    // Public methods
    bool isInside(float x, float y) const; // Checks if a point is inside the workspace
    void AddComponent(const std::string& componentName); // Adds a component to the workspace
    void Update(); // Updates the workspace
    void Render(); // Renders the workspace
    void SetSize(float newWidth, float newHeight); // Sets the size of the workspace
    std::pair<float, float> ClampPosition(float x, float y) const; // Clamps a position to the workspace bounds
    ImVec2 ClampPositionInBounds(float x, float y, float windowWidth, float windowHeight) const; // Clamps a position to the workspace bounds considering a window size
    void SetCurrentCursor(GLFWcursor* cursor); // Sets the current cursor

    // Getters
    float GetWidth() const { return width; }
    float GetHeight() const { return height; }
    float GetMenuBarHeight() const { return menuBarHeight; }
};

#endif // WORKSPACE_H