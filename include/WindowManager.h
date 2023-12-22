#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <GLFW/glfw3.h>

class WindowManager {
public:
    /**
     * @brief Constructs a new WindowManager object.
     */
    WindowManager();

    /**
     * @brief Destroys the WindowManager object.
     */
    ~WindowManager();

    /**
     * @brief Creates a new GLFW window with the specified width, height, and title.
     * 
     * @param width The width of the window.
     * @param height The height of the window.
     * @param title The title of the window.
     * @return GLFWwindow* A pointer to the created GLFW window.
     */
    GLFWwindow* createWindow(int width, int height, const char* title);

    /**
     * @brief Sets the properties of the specified GLFW window.
     * 
     * @param window A pointer to the GLFW window.
     */
    void setWindowProperties(GLFWwindow* window);

    /**
     * @brief Static key callback function that is called when a key is pressed, released, or repeated.
     * 
     * @param window A pointer to the GLFW window.
     * @param key The keyboard key that was pressed or released.
     * @param scancode The system-specific scancode of the key.
     * @param action The action that was performed (GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT).
     * @param mods Bit field describing which modifier keys were held down.
     */
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /**
     * @brief Cleans up and destroys the specified GLFW window.
     * 
     * @param window A pointer to the GLFW window.
     */
    void cleanUp(GLFWwindow* window);
};

#endif // WINDOW_MANAGER_H
