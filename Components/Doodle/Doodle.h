#pragma once

#include "imgui.h"
#include <GLFW/glfw3.h>
#include <vector>

class Doodle {
public:
    Doodle(GLFWwindow* win); // Constructor that takes a GLFWwindow
    ~Doodle(); // Destructor to clean up custom cursor
    GLFWwindow* GetWindow();
    void Render();
    void DrawLines(ImVec2 itemRectMin);
    void HandleDrawing();
    void SetWindow(GLFWwindow* win); // Method to set the GLFW window
    bool IsWindowShown() const { return showWindow; }
    void Close();
    void SetPosition(const ImVec2& pos);
    static void ResetNextID() { nextID = 0; }

private:
    static int nextID; // Static member to hold the next ID to assign
    int id; // ID of this particular Doodle
    ImVec2 canvasSize;
    std::vector<std::vector<ImVec2>> strokes;
    GLFWcursor* customCursor; // Custom cursor
    GLFWwindow* window; // GLFW window pointer
    bool showWindow = true; // Indicates if the Doodle window is shown
    ImVec2 windowPos;
    ImVec2 initialPos;
    bool firstRender = true;
};
