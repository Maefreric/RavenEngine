#include "DoodleBored.h"
#include "Workspace.h" // Include the header file for Workspace
#include <GLFW/glfw3.h> // Include the header file for GLFWwindow

DoodleBored::DoodleBored(float x, float y, float width, float height, Workspace& workspace, GLFWwindow* win)
    : Component(x, y, width, height, workspace, win) // Call the Component constructor in the initializer list
{
    // Constructor implementation
}

DoodleBored::~DoodleBored() {
    // Destructor implementation
}

std::string DoodleBored::GetName() const {
    return "DoodleBored";
}

void DoodleBored::createSquare() {
    // Implementation to create a square
    std::cout << "Creating a square..." << std::endl;
    // Add your code here to create a square
}