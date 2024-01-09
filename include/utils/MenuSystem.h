#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include <GLFW/glfw3.h>
#include "Workspace.h"
#include <string>

class MenuSystem {
private:
    Workspace& workspace;
    GLFWwindow* mainWindow;
    bool fileDialogOpen = false; // State variable to track file dialog status

public:
    MenuSystem(Workspace& workspace, GLFWwindow* window);
    void createMainMenu();
    void createFileMenu();
    void handleFileMenuItems();
    void handleFileDialog();
};

#endif // MENU_SYSTEM_H
