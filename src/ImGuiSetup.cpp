#include "ImGuiSetup.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>

void ImGuiSetup::Init(GLFWwindow* window) {
    // ####################################
    // #######-BRAND COLOR PALETTE-#######
    // raven purpleA (default)
    ImVec4 ravenPurpleA = ImVec4(0.2784f, 0.2392f, 0.2902f, 1.0f);
    // raven purpleB (darker)
    ImVec4 ravenPurpleB = ImVec4(0.2784f * 0.9f, 0.2392f * 0.9f, 0.2902f * 0.9f, 1.0f);
    // raven purpleC (lighter)
    ImVec4 ravenPurpleC = ImVec4(0.2784f * 1.1f, 0.2392f * 1.1f, 0.2902f * 1.1f, 1.0f);
    // raven black (#181818)
    ImVec4 ravenBlack = ImVec4(0.0941f, 0.0941f, 0.0941f, 1.0f);
    // raven white (#fefefe)
    ImVec4 ravenWhite = ImVec4(0.9961f, 0.9961f, 0.9961f, 1.0f);
    // raven red (#ff0000)
    ImVec4 ravenRed = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

    // ####################################

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
    style.Colors[ImGuiCol_ButtonHovered] = ravenRed; 
    style.Colors[ImGuiCol_ButtonActive] = ravenPurpleA; 
    style.Colors[ImGuiCol_FrameBg] = ravenBlack; 
    style.Colors[ImGuiCol_Text] = ravenWhite; 
    style.Colors[ImGuiCol_Header] = ravenPurpleA;
    style.Colors[ImGuiCol_HeaderHovered] = ravenPurpleB;
    style.Colors[ImGuiCol_HeaderActive] = ravenPurpleC;
    style.Colors[ImGuiCol_SliderGrab] = ravenWhite;
    style.Colors[ImGuiCol_SliderGrabActive] = ravenWhite;
    style.Colors[ImGuiCol_CheckMark] = ravenWhite;
    style.Colors[ImGuiCol_FrameBgHovered] = ravenPurpleB;
    style.Colors[ImGuiCol_FrameBgActive] = ravenPurpleC;
    style.Colors[ImGuiCol_Button] = ravenPurpleA;
    style.Colors[ImGuiCol_ResizeGrip] = ravenPurpleA;
    style.Colors[ImGuiCol_ResizeGripHovered] = ravenPurpleB;
    style.Colors[ImGuiCol_ResizeGripActive] = ravenPurpleC;
    style.Colors[ImGuiCol_FrameBgHovered] = ravenBlack;
    style.Colors[ImGuiCol_CheckMark] = ravenPurpleA;
    style.Colors[ImGuiCol_ScrollbarGrab] = ravenPurpleA;
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ravenPurpleB;
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ravenPurpleC;
    style.Colors[ImGuiCol_TitleBgCollapsed] = ravenPurpleA;
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