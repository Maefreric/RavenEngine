#define IMGUI_ENABLE_DOCKING
#include "ImGuiManager.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>

void ImGuiManager::Init(GLFWwindow* window) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 150";
    ImGui_ImplOpenGL3_Init(glsl_version);


    // Define theme colors only once
    ImVec4 PrimaryBackground(0.0941f, 0.0941f, 0.0941f, 1.0f); // "Raven Black"
    ImVec4 SecondaryBackground(0.1216f, 0.1019f, 0.1294f, 1.0f); // "Raven Shadow"
    ImVec4 TextColor(0.9961f, 0.9961f, 0.9961f, 1.0f); // "Raven White"
    ImVec4 HoverColor(0.3333f, 0.3333f, 0.3333f, 1.0f); // "Raven Hover Gray"
    ImVec4 AccentColor(0.11f, 0.11f, 0.11f, 1.0f); // Updated Accent Color for better visibility
    ImVec4 BorderColor(0.2f, 0.2f, 0.2f, 1.0f); // "Raven Border"

    // Get reference to style
    ImGuiStyle& style = ImGui::GetStyle();

    // Apply theme colors to ImGui style
    for (int i = 0; i < ImGuiCol_COUNT; i++) {
        style.Colors[i] = PrimaryBackground; // Set all elements to primary background by default
    }

    // Text
    style.Colors[ImGuiCol_Text] = TextColor;
    style.Colors[ImGuiCol_TextDisabled] = SecondaryBackground;

    // Windows and Backgrounds
    style.Colors[ImGuiCol_WindowBg] = PrimaryBackground;
    style.Colors[ImGuiCol_ChildBg] = SecondaryBackground;
    style.Colors[ImGuiCol_PopupBg] = SecondaryBackground;
    style.Colors[ImGuiCol_MenuBarBg] = PrimaryBackground;

    // Borders
    style.Colors[ImGuiCol_Border] = BorderColor;
    style.Colors[ImGuiCol_BorderShadow] = SecondaryBackground;

    // Frames
    style.Colors[ImGuiCol_FrameBg] = SecondaryBackground;
    style.Colors[ImGuiCol_FrameBgHovered] = HoverColor;
    style.Colors[ImGuiCol_FrameBgActive] = AccentColor; // Use Accent Color for active frames

    // Tabs
    style.Colors[ImGuiCol_Tab] = SecondaryBackground;
    style.Colors[ImGuiCol_TabHovered] = HoverColor;
    style.Colors[ImGuiCol_TabActive] = AccentColor; // Use Accent Color for active tabs
    style.Colors[ImGuiCol_TabUnfocused] = SecondaryBackground;
    style.Colors[ImGuiCol_TabUnfocusedActive] = AccentColor; // Use Accent Color for active unfocused tabs

    // Titles
    style.Colors[ImGuiCol_TitleBg] = PrimaryBackground;
    style.Colors[ImGuiCol_TitleBgActive] = AccentColor; // Use Accent Color for active title
    style.Colors[ImGuiCol_TitleBgCollapsed] = PrimaryBackground;

    // Headers
    style.Colors[ImGuiCol_Header] = SecondaryBackground;
    style.Colors[ImGuiCol_HeaderHovered] = HoverColor;
    style.Colors[ImGuiCol_HeaderActive] = AccentColor; // Use Accent Color for active headers

    // Buttons
    style.Colors[ImGuiCol_Button] = SecondaryBackground;
    style.Colors[ImGuiCol_ButtonHovered] = HoverColor;
    style.Colors[ImGuiCol_ButtonActive] = AccentColor; // Use Accent Color for active buttons

    // Resize Grips
    style.Colors[ImGuiCol_ResizeGrip] = SecondaryBackground;
    style.Colors[ImGuiCol_ResizeGripHovered] = HoverColor;
    style.Colors[ImGuiCol_ResizeGripActive] = AccentColor; // Use Accent Color for active resize grips

    // Scrollbars
    style.Colors[ImGuiCol_ScrollbarBg] = PrimaryBackground;
    style.Colors[ImGuiCol_ScrollbarGrab] = SecondaryBackground;
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = HoverColor;
    style.Colors[ImGuiCol_ScrollbarGrabActive] = AccentColor; // Use Accent Color for active scrollbar grabs

    // Checkmark and Sliders
    style.Colors[ImGuiCol_CheckMark] = AccentColor; // Use Accent Color for checkmarks
    style.Colors[ImGuiCol_SliderGrab] = HoverColor;
    style.Colors[ImGuiCol_SliderGrabActive] = AccentColor; // Use Accent Color for active slider grabs

    // Drag and Drop
    style.Colors[ImGuiCol_DragDropTarget] = AccentColor; // Use Accent Color for drag and drop targets

    // Navigation
    style.Colors[ImGuiCol_NavHighlight] = AccentColor; // Use Accent Color for navigation highlights
    style.Colors[ImGuiCol_NavWindowingHighlight] = AccentColor; // Use Accent Color for windowing highlights
    style.Colors[ImGuiCol_NavWindowingDimBg] = PrimaryBackground;

    // Modal Window Dim Background
    style.Colors[ImGuiCol_ModalWindowDimBg] = PrimaryBackground;

    // Set other style attributes as necessary
    style.FramePadding = ImVec2(4, 4);
    style.ItemSpacing = ImVec2(8, 4);
    style.ItemInnerSpacing = ImVec2(4, 4);

    // ... Any additional style configurations ...

    // ... Other style configurations as needed ...

    // Additional style configurations
    style.WindowRounding = 0.0f; // Square windows
    style.FrameRounding = 0.0f; // Square frames
    style.ScrollbarRounding = 0.0f; // Square scrollbars
    style.GrabRounding = 0.0f; // Square sliders/grabs
    // ... Any additional style configurations ...
}

void ImGuiManager::NewFrame() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame(); // Start ImGui OpenGL3 frame
    ImGui_ImplGlfw_NewFrame(); // Start ImGui GLFW frame
    ImGui::NewFrame(); // Start ImGui frame
}

void ImGuiManager::Render() {
    // Rendering
    ImGui::Render(); // Render ImGui
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Render ImGui draw data using OpenGL3
}

void ImGuiManager::Shutdown() {
    // Clean up ImGui
    ImGui_ImplOpenGL3_Shutdown(); // Shutdown ImGui OpenGL3 bindings
    ImGui_ImplGlfw_Shutdown(); // Shutdown ImGui GLFW bindings
    ImGui::DestroyContext(); // Destroy ImGui context
}