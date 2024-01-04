#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <unordered_map>

// Custom exception class for GLFW errors
class GLFWException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class WindowManager {
private:
    GLFWwindow* mainWindow; // Main window
    std::unordered_map<std::string, GLFWwindow*> componentWindows; // Map to hold component windows

public:
    WindowManager();
    ~WindowManager();

    GLFWwindow* createWindow(int width, int height, const char* title, bool isComponentWindow = false, const std::string& componentName = "");
    void setWindowProperties(GLFWwindow* window);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void cleanUp();

    // New Methods
    void destroyComponentWindow(const std::string& componentName);
    GLFWwindow* getComponentWindow(const std::string& componentName);

    // Getter for main window
    GLFWwindow* getMainWindow() const;
};

#endif // WINDOW_MANAGER_H