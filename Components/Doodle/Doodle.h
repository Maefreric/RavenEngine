#pragma once
#include "..\Components.h" // Ensure this includes the definition of the Component class
#include <GLFW/glfw3.h>
#include <vector>
// Include for ImVec2 (part of ImGui)
#include "imgui.h" 
#include <iostream>

class Workspace; // Forward declaration if Workspace is used

class Doodle : public Component {
public:
    Doodle(float x, float y, float width, float height, Workspace& workspace, GLFWwindow* win);
    ~Doodle();

    // Interface methods for ComponentsManager
    void Update() override;
    void PreRender() override;

    // Control methods
    bool IsWindowShown() const;
    void SetPosition(const ImVec2& pos);
    void ToggleChalkboardMode();
    

    // Getter and Setter for window
    GLFWwindow* GetWindow();
    void SetWindow(GLFWwindow* win);
    

private:
    // Member variables
    static int nextID;
    int id;
    ImVec2 initialPos;
    GLFWwindow* window;
    bool showWindow = true;
    bool firstRender = true;
    GLFWcursor* pencilCursor = nullptr;
    GLFWcursor* eraseCursor = nullptr;
    GLFWcursor* currentCursor = nullptr;
    bool eraseMode = false;
    ImU32 canvasColor = IM_COL32(245, 245, 220, 255);
    ImU32 lineColor = IM_COL32(0, 0, 0, 255);
    bool isDrawing = false;
    bool chalkboardMode = false;
    std::vector<std::vector<ImVec2>> strokes;
    bool skipRendering = false;
    float lineThickness = 1.0f; // Added lineThickness member variable
    bool isDrawingStraightLine = false; // Added isDrawingStraightLine member variable
    ImVec2 straightLineStart; // Added straightLineStart member variable

    // Private helper methods
    void InitializeCursors();
    GLFWcursor* LoadCursor(const char* imagePath);
    void UpdateCursor(GLFWcursor* desiredCursor);
    void UpdateCursorState();
    
    void PostRender() override;
    void RenderCanvas();
    void RenderContextMenu();
    void RenderModeMenuItems();
    void RenderClearCanvasButton();
    void RenderSizeSection();
    void RenderColorSection();
    void RenderCloseButton();
    void DrawLines(ImVec2 itemRectMin);
    void HandleDrawing();
    void AddPointToStroke(const ImVec2& point);
    void EraseLines(const ImVec2& eraseCenter);
};