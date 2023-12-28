#include "DoodleManager.h"
#include <iostream>
#include <algorithm>

ImVec2 DoodleManager::lastWindowPos = ImVec2(0, 0);

DoodleManager::~DoodleManager() {
    for (auto& doodle : doodleWindows) {
        delete doodle;
    }
    doodleWindows.clear();
}

void DoodleManager::CreateNewDoodle(GLFWwindow* mainWin) {
    Doodle* newDoodle = new Doodle(mainWin);
    if (doodleWindows.empty()) {
        lastWindowPos = ImVec2(200, 200); // Starting position for the first window
    } else {
        lastWindowPos.x += 30; // Cascading effect
        lastWindowPos.y += 30;
    }
    newDoodle->SetPosition(lastWindowPos);
    doodleWindows.push_back(newDoodle);
}


void DoodleManager::RenderDoodles() {
    for (auto it = doodleWindows.begin(); it != doodleWindows.end();) {
        Doodle* doodle = *it;
        if (doodle->IsWindowShown()) {
            doodle->Render();
            ++it;
        } else {
            doodle->Close();
            delete doodle;
            it = doodleWindows.erase(it);
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
    // If there are no Doodle windows, reset the next ID
    if (doodleWindows.empty()) {
        Doodle::ResetNextID();
    }
}

std::vector<Doodle*>& DoodleManager::GetDoodleWindows() {
    return doodleWindows;
}