#pragma once

#include "imgui.h"
#include <GLFW/glfw3.h>
#include <vector>

class Doodle {
public:
    Doodle(GLFWwindow* win);
    ~Doodle();
    GLFWwindow* GetWindow();
    void Render();
    void DrawLines(ImVec2 itemRectMin);
    void HandleDrawing();
    void SetWindow(GLFWwindow* win);
    bool IsWindowShown() const { return showWindow; }
    void Close();
    void SetPosition(const ImVec2& pos);
    static void ResetNextID() { nextID = 0; }
    bool PreRender();
    void PostRender();
    void ToggleChalkboardMode();
    void EraseLines(const ImVec2& eraseCenter);
    void AddPointToStroke(const ImVec2& point);
    void UpdateCursorState();
    ImVec2 straightLineStart;
    bool isDrawingStraightLine = false;

private:
    static int nextID; 
    int id; 
    ImVec2 canvasSize;
    std::vector<std::vector<ImVec2>> strokes;
    GLFWcursor* customCursor = nullptr;
    GLFWcursor* eraseCursor = nullptr; 
    GLFWwindow* window; 
    bool showWindow = true; 
    ImVec2 windowPos;
    ImVec2 initialPos;
    bool firstRender = true;
    GLFWcursor* currentCursor = nullptr;
    void UpdateCursor(GLFWcursor* desiredCursor);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_None; // Single declaration
    bool noResize = false;
    bool chalkboardMode = false;
    bool eraseMode = false;
    ImU32 canvasColor = IM_COL32(245, 245, 220, 255); 
    ImU32 lineColor = IM_COL32(0, 0, 0, 255); 
    bool isDrawing = false;
    bool lockCanvasSize = false; 
    ImVec4 UserCustomBGColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); 
    ImVec4 UserCustomLineColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
};