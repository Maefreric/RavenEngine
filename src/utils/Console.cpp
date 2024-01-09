#include "Console.h"
#include <imgui.h>

namespace RavenEngine {

void Console::AddLog(const std::string& message) {
    log.push_back(message);
}

void Console::Draw(const char* title, bool* p_open) {
    ImGui::SetNextWindowSize(ImVec2(600, 200)); // Set the window size to 600x200
    ImGui::SetNextWindowPos(ImVec2(400, 800)); // Set the window position to 400x800

    if (!ImGui::Begin(title, p_open)) {
        ImGui::End();
        return;
    }

    // Display every log message in the ImGui window
    for (const auto& message : log) {
        ImGui::TextUnformatted(message.c_str());
    }

    ImGui::End();
}

} // namespace RavenEngine
