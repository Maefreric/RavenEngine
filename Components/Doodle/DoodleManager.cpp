#include "DoodleManager.h"
#include <iostream>
#include <algorithm>

ImVec2 DoodleManager::lastWindowPos = ImVec2(0, 0);

void DoodleManager::CreateNewDoodle(GLFWwindow* mainWin) {
    std::cout << "Creating a new Doodle instance..." << std::endl;

    // Dynamically allocate a new Doodle instance
    Doodle* newDoodle = new Doodle(mainWin);
    newDoodle->SetPosition(lastWindowPos);
    lastWindowPos.x += 20;
    lastWindowPos.y += 20;
    doodleWindows.push_back(newDoodle);

    std::cout << "New Doodle instance created. Total count: " << doodleWindows.size() << std::endl;
}

void DoodleManager::RenderDoodles() {
    for (auto& doodle : doodleWindows) {
        if (doodle->IsWindowShown()) {
            doodle->Render();
        } else {
            doodle->Close();
        }
    }

    // Delete Doodle instances that are no longer needed and remove them from the vector
    doodleWindows.erase(std::remove_if(doodleWindows.begin(), doodleWindows.end(),
                                       [](Doodle* d) {
                                           if (!d->IsWindowShown()) {
                                               delete d;
                                               return true;
                                           }
                                           return false;
                                       }),
                        doodleWindows.end());
}

std::vector<Doodle*>& DoodleManager::GetDoodleWindows() {
    return doodleWindows;
}
