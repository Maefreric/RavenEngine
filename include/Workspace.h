#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <GLFW/glfw3.h>
#include <string>
#include <memory>
#include "ComponentsManager.h" // Include ComponentsManager

class Workspace {
public:
    Workspace(int width, int height, int menuBarHeight, GLFWwindow* window);
    bool isInside(int x, int y) const;
    void AddComponent(const std::string& componentName);
    void Update();
    void Render();

private:
    int width;
    int height;
    int menuBarHeight;
    GLFWwindow* window;
    ComponentsManager componentsManager; // Manages the components
};

#endif // WORKSPACE_H
