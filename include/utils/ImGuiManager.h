#ifndef IMGImGuiManager_SETUP_H
#define IMGImGuiManager_SETUP_H

#define IMGUI_ENABLE_DOCKING
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

class ImGuiManager {
public:
    /**
     * @brief Initializes the ImGui context.
     * 
     * @param window The GLFW window to associate with ImGui.
     */
    static void Init(GLFWwindow* window);

    /**
     * @brief Starts a new ImGui frame.
     */
    static void NewFrame();

    /**
     * @brief Renders the ImGui draw data.
     */
    static void Render();

    /**
     * @brief Shuts down the ImGui context.
     */
    static void Shutdown();
};

#endif // IMGImGuiManager_SETUP_H