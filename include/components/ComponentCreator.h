#ifndef COMPONENTCREATOR_H
#define COMPONENTCREATOR_H

#include "Component.h"
#include <memory>
#include <string>
#include <GLFW/glfw3.h>

class Workspace; // Forward declaration

class ComponentCreator {
public:
    static std::unique_ptr<Component> CreateComponent(const std::string& type, 
                                                  float x, float y, 
                                                  float width, float height);

};

#endif // COMPONENTCREATOR_H