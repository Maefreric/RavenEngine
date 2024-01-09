#pragma once
#include <string>
#include <vector>

namespace RavenEngine {

class Console {
public:
    void AddLog(const std::string& message); // Add a log message
    void Draw(const char* title, bool* p_open = nullptr); // Render the console window

private:
    std::vector<std::string> log; // Stores all the log messages
    // Other members as needed (e.g., command history, input buffer)
};

} // namespace RavenEngine
