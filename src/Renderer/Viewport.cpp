#include "../include/Renderer/Renderer.h"
#include "Viewport.h"
#include <GLFW/glfw3.h>
#include "imgui.h"
#include <iostream>

Viewport::Viewport(GLFWwindow* win) : window(win), size(ImVec2(800, 600)) {
    std::cout << "Initializing Viewport..." << std::endl;

    // Set up the Framebuffer
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // Create a color attachment texture
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, static_cast<GLsizei>(size.x), static_cast<GLsizei>(size.y), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Initialize Renderer
    renderer.Initialize(static_cast<int>(size.x), static_cast<int>(size.y));

    std::cout << "Viewport initialized successfully." << std::endl;
}

Viewport::~Viewport() {
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &textureColorbuffer);

    renderer.Shutdown();

    std::cout << "Viewport resources cleaned up successfully." << std::endl;
}

void Viewport::Render() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});

    // Set the default size and position for the viewport window
    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver); // Set default size
    ImGui::SetNextWindowPos(ImVec2(600, 50), ImGuiCond_FirstUseEver);    // Set default position

    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    if (viewportPanelSize.x != size.x || viewportPanelSize.y != size.y) {
        renderer.OnWindowResize(static_cast<int>(viewportPanelSize.x), static_cast<int>(viewportPanelSize.y));
        size.x = viewportPanelSize.x;
        size.y = viewportPanelSize.y;
    }

    renderer.BeginScene();
    float color[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    renderer.Clear(color);
    // Perform your rendering here
    renderer.EndScene();

    ImGui::Image(reinterpret_cast<void*>(static_cast<uintptr_t>(textureColorbuffer)), ImVec2{size.x, size.y}, ImVec2{0, 0}, ImVec2{1, 1});

    ImGui::End();
    ImGui::PopStyleVar();
}


void Viewport::Resize(int newWidth, int newHeight) {
    renderer.OnWindowResize(newWidth, newHeight);
}
