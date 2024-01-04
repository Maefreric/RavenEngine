#ifndef DOODLEBORED_H
#define DOODLEBORED_H

#include <iostream>

#include "..\Components\Components.h" // Include the header file for Component
#include "Workspace.h" // Include the header file for Workspace
#include <GLFW/glfw3.h> // Include the header file for GLFWwindow

class DoodleBored : public Component {
public:
    DoodleBored(float x, float y, float width, float height, Workspace& workspace, GLFWwindow* win);
    ~DoodleBored();

    std::string GetName() const override; // Override GetName method from Component
    void createSquare(); // Declare createSquare method
};

#endif // DOODLEBORED_H