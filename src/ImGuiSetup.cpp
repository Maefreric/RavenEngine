#include "ImGuiSetup.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>

// Initialize static member variables with the brand color palette
ImVec4 ImGuiSetup::ravenPurpleA(0.2784f, 0.2392f, 0.2902f, 1.0f);
ImVec4 ImGuiSetup::ravenPurpleB(0.2506f, 0.2153f, 0.2612f, 1.0f);
ImVec4 ImGuiSetup::ravenPurpleC(0.3062f, 0.2631f, 0.3192f, 1.0f);
ImVec4 ImGuiSetup::ravenBlack(0.0941f, 0.0941f, 0.0941f, 1.0f);
ImVec4 ImGuiSetup::ravenWhite(0.9961f, 0.9961f, 0.9961f, 1.0f);
ImVec4 ImGuiSetup::ravenRed(1.0f, 0.0f, 0.0f, 1.0f);

void ImGuiSetup::Init(GLFWwindow* window) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION(); // Check ImGui version
    ImGui::CreateContext(); // Create ImGui context
    ImGuiIO& io = ImGui::GetIO(); (void)io; // Get ImGui IO
    
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Initialize ImGui GLFW bindings
    const char* glsl_version = "#version 150";
    ImGui_ImplOpenGL3_Init(glsl_version); // Initialize ImGui OpenGL3 bindings

    // Change the default highlighted color
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_ButtonHovered] = ImGuiSetup::ravenRed; 
    style.Colors[ImGuiCol_ButtonActive] = ImGuiSetup::ravenPurpleA; 
    style.Colors[ImGuiCol_FrameBg] = ImGuiSetup::ravenBlack; 
    style.Colors[ImGuiCol_Text] = ImGuiSetup::ravenWhite; 
    style.Colors[ImGuiCol_Header] = ImGuiSetup::ravenPurpleA;
    style.Colors[ImGuiCol_HeaderHovered] = ImGuiSetup::ravenPurpleB;
    style.Colors[ImGuiCol_HeaderActive] = ImGuiSetup::ravenPurpleC;
    style.Colors[ImGuiCol_SliderGrab] = ImGuiSetup::ravenWhite;
    style.Colors[ImGuiCol_SliderGrabActive] = ImGuiSetup::ravenWhite;
    style.Colors[ImGuiCol_CheckMark] = ImGuiSetup::ravenPurpleA;
    style.Colors[ImGuiCol_FrameBgHovered] = ImGuiSetup::ravenBlack;
    style.Colors[ImGuiCol_FrameBgActive] = ImGuiSetup::ravenPurpleC;
    style.Colors[ImGuiCol_Button] = ImGuiSetup::ravenPurpleA;
    style.Colors[ImGuiCol_ResizeGrip] = ImGuiSetup::ravenPurpleA;
    style.Colors[ImGuiCol_ResizeGripHovered] = ImGuiSetup::ravenPurpleB;
    style.Colors[ImGuiCol_ResizeGripActive] = ImGuiSetup::ravenPurpleC;
    style.Colors[ImGuiCol_ScrollbarGrab] = ImGuiSetup::ravenPurpleA;
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImGuiSetup::ravenPurpleB;
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImGuiSetup::ravenPurpleC;
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImGuiSetup::ravenPurpleA;
    style.Colors[ImGuiCol_TitleBgActive] = ImGuiSetup::ravenPurpleA;
}

void ImGuiSetup::NewFrame() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame(); // Start ImGui OpenGL3 frame
    ImGui_ImplGlfw_NewFrame(); // Start ImGui GLFW frame
    ImGui::NewFrame(); // Start ImGui frame
}

void ImGuiSetup::Render() {
    // Rendering
    ImGui::Render(); // Render ImGui
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // Render ImGui draw data using OpenGL3
}

void ImGuiSetup::Shutdown() {
    // Clean up ImGui
    ImGui_ImplOpenGL3_Shutdown(); // Shutdown ImGui OpenGL3 bindings
    ImGui_ImplGlfw_Shutdown(); // Shutdown ImGui GLFW bindings
    ImGui::DestroyContext(); // Destroy ImGui context
}