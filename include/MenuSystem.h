#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

// Add the include path for GLFW
#include <GLFW/glfw3.h>

class MenuSystem {
public:
    // Constructor
    MenuSystem();

    // Method to create the main menu bar
    void createMainMenu(GLFWwindow* window);
};

#endif // MENU_SYSTEM_H
