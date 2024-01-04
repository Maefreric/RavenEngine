#ifndef IMGUI_SETUP_H
#define IMGUI_SETUP_H
#include "imgui.h"
#include <GLFW/glfw3.h>

class ImGuiSetup {
public:
    // Declare the static color variables
    static ImVec4 ravenPurpleA;
    static ImVec4 ravenPurpleB;
    static ImVec4 ravenPurpleC;
    static ImVec4 ravenBlack;
    static ImVec4 ravenWhite;
    static ImVec4 ravenRed;


    // ####################################
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

#endif // IMGUI_SETUP_H
