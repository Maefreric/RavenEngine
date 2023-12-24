#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include <GLFW/glfw3.h>

class MenuSystem {
public:
    // Constructor
    MenuSystem();

    // Method to create the main menu bar
    void createMainMenu(GLFWwindow* window);

    // Method to open a file dialog
    bool OpenFileDialog(char* selectedFile, int bufferSize, GLFWwindow* ownerWindow);
};

#endif // MENU_SYSTEM_H
