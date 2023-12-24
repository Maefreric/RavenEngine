#include "WindowManager.h"
#include <iostream>
#include <stdexcept>

// Initialize the static member variable
GLFWwindow* WindowManager::window = nullptr;

// Constructor
WindowManager::WindowManager() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
}

// Destructor
WindowManager::~WindowManager() {
    glfwTerminate();
}

// Create a GLFW window with specified width, height, and title
GLFWwindow* WindowManager::createWindow(int width, int height, const char* title) {
    // Set window hints
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    // Create the GLFW window
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Make the GLFW window the current context
    glfwMakeContextCurrent(window);

    return window;
}

// Set window properties such as size limits, opacity, and key callback
void WindowManager::setWindowProperties(GLFWwindow* window) {
    glfwSetWindowSizeLimits(window, 800, 600, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetKeyCallback(window, keyCallback);
}

// Key callback function to handle key events
void WindowManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

// Clean up and destroy the GLFW window
void WindowManager::cleanUp(GLFWwindow* window) {
    if (window) {
        glfwDestroyWindow(window);
    }
}
