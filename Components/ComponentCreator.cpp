#include "ComponentCreator.h"
#include "Doodle/Doodle.h" // Include the specific component types you have
#include "Doodle/DoodleBored.h"

std::unique_ptr<Component> ComponentCreator::CreateComponent(const std::string& type, float x, float y, float width, float height, Workspace& workspace, GLFWwindow* win) {
    if (type == "Doodle") {
        std::cout << "Creating Doodle component." << std::endl;
        return std::make_unique<Doodle>(x, y, width, height, workspace, win);
    }
    if (type == "Doodle Bored") {
        std::cout << "Attempting to create Doodle Bored component." << std::endl;
        auto component = std::make_unique<DoodleBored>(x, y, width, height, workspace, win);
        std::cout << "Successfully created Doodle Bored component." << std::endl;
        return component;
    }
    return nullptr;
}
