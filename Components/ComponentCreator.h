#ifndef COMPONENTCREATOR_H
#define COMPONENTCREATOR_H

#include "Components.h"
#include <memory>
#include <string> // Include the string header
#include <GLFW/glfw3.h>


class ComponentCreator {
public:
    // Assuming you have different types of components, you can use an enum or string to specify the type.
    static std::unique_ptr<Component> CreateComponent(const std::string& type, int x, int y, Workspace& workspace, GLFWwindow* win);
};

#endif // COMPONENTCREATOR_H