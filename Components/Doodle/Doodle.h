#pragma once

#include "imgui.h"
#include <GLFW/glfw3.h>
#include <vector>

class Doodle {
public:
    Doodle(GLFWwindow* win);
    ~Doodle();
    GLFWwindow* GetWindow();
    void SetWindow(GLFWwindow* win);
    static void ResetNextID() { nextID = 0; }
    bool IsWindowShown() const { return showWindow; }
    void Close();
    void SetPosition(const ImVec2& pos);

    void UpdateCursorState();

    bool PreRender();
    void Render();
    void PostRender();

    ImVec2 straightLineStart;
    void DrawLines(ImVec2 itemRectMin);
    void HandleDrawing();
    void AddPointToStroke(const ImVec2& point);
    void EraseLines(const ImVec2& eraseCenter);
    bool isDrawingStraightLine = false;
    
    void ToggleChalkboardMode();

private:
    static int nextID; 
    int id; 
    ImVec2 canvasSize;

    GLFWwindow* window; 
    bool showWindow = true; 
    ImVec2 windowPos;
    ImVec2 initialPos;

    GLFWcursor* customCursor = nullptr;
    GLFWcursor* eraseCursor = nullptr; 
    GLFWcursor* currentCursor = nullptr;
    void UpdateCursor(GLFWcursor* desiredCursor);

    bool firstRender = true;

    std::vector<std::vector<ImVec2>> strokes;
    bool eraseMode = false;

    ImU32 canvasColor = IM_COL32(245, 245, 220, 255); 
    ImU32 lineColor = IM_COL32(0, 0, 0, 255); 
    bool isDrawing = false;
    ImVec4 UserCustomBGColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); 
    ImVec4 UserCustomLineColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

    bool chalkboardMode = false;    
};