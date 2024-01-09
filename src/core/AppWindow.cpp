#include <glad/glad.h>
#include <iostream>
#include "Core/AppWindow.h"

AppWindow::AppWindow(int width, int height, const char* title) 
    : mainWindow(nullptr), isWindowInitialized(false) {
    std::cout << "Initializing AppWindow..." << std::endl;
    initGLFW();
    mainWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!mainWindow) {
        throw GLFWException("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(mainWindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    std::cout << "Current context: " << glfwGetCurrentContext() << std::endl;
    std::cout << "Main window: " << mainWindow << std::endl;

    // Enable VSync
    glfwSwapInterval(1);  // 1 means VSync is enabled, 0 would mean it's disabled

    setWindowProperties(mainWindow);
    glfwSetWindowUserPointer(mainWindow, this);
    glfwMaximizeWindow(mainWindow);
    isWindowInitialized = true;
    std::cout << "AppWindow initialized successfully." << std::endl;
}

void AppWindow::initGLFW() {
    std::cout << "Initializing GLFW..." << std::endl;
    if (!glfwInit()) {
        throw GLFWException("Failed to initialize GLFW");
    }
    std::cout << "GLFW initialized successfully." << std::endl;
}

AppWindow::~AppWindow() {
    std::cout << "Cleaning up AppWindow..." << std::endl;
    cleanUp();
    std::cout << "AppWindow cleaned up successfully." << std::endl;
}

void AppWindow::setWindowProperties(GLFWwindow* window) {
    std::cout << "Setting window properties..." << std::endl;
    glfwSetWindowSizeLimits(window, 800, 600, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    std::cout << "Window properties set successfully." << std::endl;
}

void AppWindow::pollEvents() {
    
    glfwPollEvents();
}

void AppWindow::swapBuffers() {
    
    if (mainWindow) {
        glfwSwapBuffers(mainWindow);
    }
}

bool AppWindow::shouldClose() const {
    return glfwWindowShouldClose(mainWindow);
}

void AppWindow::cleanUp() {
    std::cout << "Cleaning up..." << std::endl;
    if (mainWindow) {
        glfwDestroyWindow(mainWindow);
        mainWindow = nullptr;
    }
    if (isWindowInitialized) {
        glfwTerminate();
    }
    std::cout << "Clean up completed." << std::endl;
}

GLFWwindow* AppWindow::getMainWindow() const {
    std::cout << "Getting main window..." << std::endl;
    return mainWindow;
}

// Define the static callback methods as needed
void AppWindow::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    std::cout << "Key callback triggered..." << std::endl;
    // Implementation here
}

void AppWindow::windowSizeCallback(GLFWwindow* window, int width, int height) {
    std::cout << "Window size callback triggered..." << std::endl;
    // Implementation here
}