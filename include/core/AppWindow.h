#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <GLFW/glfw3.h>
#include <stdexcept>

class GLFWException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class AppWindow {
private:
    GLFWwindow* mainWindow;
    bool isWindowInitialized;

    void initGLFW();
    void setWindowProperties(GLFWwindow* window);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void windowSizeCallback(GLFWwindow* window, int width, int height);

public:
    AppWindow(int width, int height, const char* title);
    ~AppWindow();

    void pollEvents();
    void swapBuffers();
    bool shouldClose() const;
    void cleanUp();
    GLFWwindow* getMainWindow() const;

    // Additional functionality as needed for the main window
};

#endif // APP_WINDOW_H
