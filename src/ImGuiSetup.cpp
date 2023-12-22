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
