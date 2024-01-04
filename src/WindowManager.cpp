#include "WindowManager.h"
#include <iostream>
#include <stdexcept>
#include <GLFW/glfw3.h>

WindowManager::WindowManager() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
}

WindowManager::~WindowManager() {
    cleanUp();
    glfwTerminate();
}

GLFWwindow* WindowManager::createWindow(int width, int height, const char* title, bool isComponentWindow, const std::string& componentName) {
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    setWindowProperties(window);

    if (isComponentWindow) {
        componentWindows[componentName] = window;
    } else {
        mainWindow = window;
    }

    return window;
}

void WindowManager::setWindowProperties(GLFWwindow* window) {
    glfwSetWindowSizeLimits(window, 800, 600, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetKeyCallback(window, keyCallback);
}

void WindowManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void WindowManager::cleanUp() {
    if (mainWindow) {
        glfwDestroyWindow(mainWindow);
        mainWindow = nullptr;
    }

    for (auto& pair : componentWindows) {
        glfwDestroyWindow(pair.second);
    }

    componentWindows.clear();
}

void WindowManager::destroyComponentWindow(const std::string& componentName) {
    auto it = componentWindows.find(componentName);
    if (it != componentWindows.end()) {
        glfwDestroyWindow(it->second);
        componentWindows.erase(it);
    }
}

GLFWwindow* WindowManager::getComponentWindow(const std::string& componentName) {
    auto it = componentWindows.find(componentName);
    if (it != componentWindows.end()) {
        return it->second;
    }
    return nullptr;
}