#include "ComponentCreator.h"
#include "Doodle/Doodle.h" // Include specific component headers here

std::unique_ptr<Component> ComponentCreator::CreateComponent(const std::string& type, int x, int y, Workspace& workspace, GLFWwindow* win) {
    if (type == "Doodle") {
        return std::make_unique<Doodle>(x, y, workspace, win);
    }
    // Add more else if blocks here for other component types

    // If the type is not recognized, return nullptr or throw an exception
    return nullptr;
}
