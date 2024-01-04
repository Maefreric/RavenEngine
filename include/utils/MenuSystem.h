#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

// Add the include path for GLFW
#include <GLFW/glfw3.h>
#include <vector> // Include the vector header
#include "Workspace.h"

class MenuSystem {
public:
    // Constructor
    MenuSystem(Workspace& workspace);

    // Method to create the main menu bar
    void createMainMenu(GLFWwindow* window);

    // Declare the OpenFileDialog function as a member function
    bool OpenFileDialog(char* selectedFile, int bufferSize, GLFWwindow* ownerWindow);

private:
    Workspace& workspace;
    
};

#endif // MENU_SYSTEM_H