#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

// Add the include path for GLFW
#include <GLFW/glfw3.h>
#include "Doodle.h" // Include the Doodle header
#include <vector> // Include the vector header
#include "DoodleManager.h" // Include the DoodleManager header

class MenuSystem {
public:
    // Constructor
    MenuSystem();

    // Method to create the main menu bar
    void createMainMenu(GLFWwindow* window, DoodleManager& doodleManager);

    // Declare the OpenFileDialog function as a member function
    bool OpenFileDialog(char* selectedFile, int bufferSize, GLFWwindow* ownerWindow);

    std::vector<Doodle>& getDoodleWindows();

private:
    std::vector<Doodle> doodleWindows;
};

#endif // MENU_SYSTEM_H