#ifndef COMPONENTCREATOR_H
#define COMPONENTCREATOR_H

#include "Component.h"
#include <memory>
#include <string> // Include the string header
#include <GLFW/glfw3.h>
#include <iostream>

class Workspace; // Forward declaration

class ComponentCreator {
public:
    // Change this method to accept float parameters for the position and size
    static std::unique_ptr<Component> CreateComponent(const std::string& type, float x, float y, float width, float height, Workspace& workspace, GLFWwindow* win);

    // ... other methods ...
};

#endif // COMPONENTCREATOR_H