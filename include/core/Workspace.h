#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <GLFW/glfw3.h>
#include <string>
#include "ComponentManager.h"
#include "../renderer/Viewport.h"
#include "../utils/SceneHierarchyPanel.h"
#include "../core/Scene.h"
#include "../utils/Console.h" // Include the Console header

class Workspace {
private:
    GLFWwindow* window;
    ComponentManager componentManager;
    Viewport viewport;
    RavenEngine::SceneHierarchyPanel sceneHierarchyPanel;
    RavenEngine::Scene currentScene;
    RavenEngine::Console console; // Add the Console member

public:
    explicit Workspace(GLFWwindow* window);
    void AddComponent(const std::string& componentName);
    void Update();
    void Render();
    bool isInside(float x, float y) const;
    void OnImGuiRender();
    void OnViewportResize(uint32_t width, uint32_t height);
    RavenEngine::Scene& GetCurrentScene();
    void NewScene();
    void OpenScene();
    void SaveSceneAs();

    // Other member function declarations...
};

#endif // WORKSPACE_H