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
    void DrawLines(ImVec2 itemRectMin); // Method to draw lines
    void HandleDrawing();
    void SetWindow(GLFWwindow* win); // Method to set the GLFW window
    bool IsWindowShown() const { return showWindow; }
    void Close();
    void SetPosition(const ImVec2& pos);
    static void ResetNextID() { nextID = 0; }
    bool PreRender();
    void PostRender();
    void ToggleChalkboardMode();
    void EraseLines(const ImVec2& eraseCenter);
    void AddPointToStroke(const ImVec2& point);
    void UpdateCursorState();// Add this line
    ImVec2 straightLineStart;
    bool isDrawingStraightLine = false;

private:
    static int nextID; // Static member to hold the next ID to assign
    int id; // ID of this particular Doodle
    ImVec2 canvasSize;
    std::vector<std::vector<ImVec2>> strokes;
    GLFWcursor* customCursor = nullptr; // Custom cursor for drawing
    GLFWcursor* eraseCursor = nullptr; // Custom cursor for erasing
    GLFWwindow* window; // GLFW window pointer
    bool showWindow = true; // Indicates if the Doodle window is shown
    ImVec2 windowPos;
    ImVec2 initialPos;
    bool firstRender = true;
    GLFWcursor* currentCursor = nullptr; // Track the currently set cursor
    void UpdateCursor(GLFWcursor* desiredCursor); // Method to update the cursor

    // chalkboardMode, eraseMode and canvasColor are new
    bool chalkboardMode = false;
    bool eraseMode = false; // New variable for erase mode
    ImU32 canvasColor = IM_COL32(245, 245, 220, 255); // Default paper color
    ImU32 lineColor = IM_COL32(0, 0, 0, 255); // Default line color
    bool isDrawing = false;
};