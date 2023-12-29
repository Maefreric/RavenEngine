#include "ImGuiSetup.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <iostream>

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
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Red
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.2784f, 0.2392f, 0.2902f, 1.0f); // Your brand color

    // Set the colors for the color picker background and text
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.0941f, 0.0941f, 0.0941f, 1.0f); // Dark grey background
    style.Colors[ImGuiCol_Text] = ImVec4(0.9961f, 0.9961f, 0.9961f, 1.0f); // Almost white text

    // Set the colors for hovered and active menu items
    //the default bg state color is fine
    // Your brand color for active menu item something like style.Colors[ImGuiCol_MenuItemActive] = ImVec4(0.2784f, 0.2392f, 0.2902f, 1.0f);  but since menuitemactive isnt a thing we have to do it a different way
    style.Colors[ImGuiCol_Header] = ImVec4(0.2784f, 0.2392f, 0.2902f, 1.0f); // Dark purple for selected menu item
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.2784f * 0.9f, 0.2392f * 0.9f, 0.2902f * 0.9f, 1.0f); // Darker purple for hovered menu item
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.2784f * 1.1f, 0.2392f * 1.1f, 0.2902f * 1.1f, 1.0f); // Lighter purple for selected menu item

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
