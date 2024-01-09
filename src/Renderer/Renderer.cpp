#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>

using namespace RavenEngine;

Renderer::Renderer() : screenWidth(800), screenHeight(600), fbo(0), textureColorbuffer(0) {
    // Constructor logic
}

Renderer::~Renderer() {
    Shutdown(); // Ensure resources are cleaned up
}

bool Renderer::Initialize(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // Handle the error in case GLAD fails to initialize
        return false;
    }

    SetViewport(0, 0, screenWidth, screenHeight);
    createFramebuffer(); // Call this function to set up the framebuffer

    // Additional initialization logic can go here

    return true;
}

void Renderer::Shutdown() {
    deleteFramebuffer(); // Clean up the framebuffer and its associated texture
}

void Renderer::BeginScene() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Renderer::EndScene() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::Clear(const float* clearColor) {
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}

void Renderer::OnWindowResize(int newWidth, int newHeight) {
    screenWidth = newWidth;
    screenHeight = newHeight;
    SetViewport(0, 0, newWidth, newHeight);

    // Resize the texture attached to the framebuffer
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Renderer::GetRenderedTexture() const {
    return textureColorbuffer;
}

void Renderer::createFramebuffer() {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::deleteFramebuffer() {
    glDeleteTextures(1, &textureColorbuffer);
    glDeleteFramebuffers(1, &fbo);
}
