#pragma once

#include "Doodle.h"
#include <GLFW/glfw3.h>
#include <vector>

class DoodleManager {
public:
    DoodleManager() = default;
    ~DoodleManager();  // Add this line

    void CreateNewDoodle(GLFWwindow* window);
    void RenderDoodles();
    
    // Make doodleWindows and GetDoodleWindows public
    std::vector<Doodle*>& GetDoodleWindows();

    static ImVec2 lastWindowPos;

private:
    std::vector<Doodle*> doodleWindows;
};