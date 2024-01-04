#include "Doodle.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <../include/Workspace.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/stb/stb_image.h"

int Doodle::nextID = 0; // init ID# to 0
 // Constructors/Destructors
Doodle::Doodle(float x, float y, float width, float height, Workspace& workspace, GLFWwindow* win)
    : Component(x, y, width, height, workspace, win), id(nextID++) {
    if (!win) {
        std::cerr << "Doodle constructor error: GLFWwindow pointer is null." << std::endl;
        throw std::runtime_error("GLFWwindow pointer is null in Doodle constructor");
    }
    if (glfwWindowShouldClose(win)) {
        std::cerr << "Doodle constructor error: GLFWwindow pointer is not valid." << std::endl;
        throw std::runtime_error("GLFWwindow pointer is not valid in Doodle constructor");
    }
    std::cout << "Doodle constructor initializing..." << std::endl;
    InitializeCursors();
    std::cout << "Doodle constructor initialized." << std::endl;
    std::cout << "Doodle constructor: window = " << window << std::endl;
}
Doodle::~Doodle() {
    if (pencilCursor) {
        glfwDestroyCursor(pencilCursor);
        pencilCursor = nullptr; // Set to nullptr after destruction
    }
    if (eraseCursor) {
        glfwDestroyCursor(eraseCursor);
        eraseCursor = nullptr; // Set to nullptr after destruction
    }
}

void Doodle::SetPosition(const ImVec2& pos) {
    initialPos = pos;
    firstRender = true;
}

GLFWcursor* Doodle::LoadCursor(const char* imagePath) {
    int cursorWidth, cursorHeight, cursorChannels;
    unsigned char* cursorPixels = stbi_load(imagePath, &cursorWidth, &cursorHeight, &cursorChannels, 4);
    if (!cursorPixels) {
        std::cerr << "Failed to load cursor image: " << imagePath << std::endl;
        throw std::runtime_error("Failed to load cursor image");
    }

    GLFWimage cursorImage{cursorWidth, cursorHeight, cursorPixels};
    GLFWcursor* cursor = glfwCreateCursor(&cursorImage, 0, 0);
    stbi_image_free(cursorPixels);
    return cursor;
}

void Doodle::InitializeCursors() {
    pencilCursor = LoadCursor("../Components/Doodle/Assets/pencil.png");
    eraseCursor = LoadCursor("../Components/Doodle/Assets/eraser.png");

    if (pencilCursor && eraseCursor) {
        std::cout << "Doodle::InitializeCursors SUCCESS" << std::endl;
    } else {
        std::cerr << "Error loading cursors" << std::endl;
        // Handle the error appropriately
    }

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
}

void Doodle::UpdateCursor(GLFWcursor* desiredCursor) {
    if (currentCursor != desiredCursor) {
        workspace.SetCurrentCursor(desiredCursor);
        currentCursor = desiredCursor;
    }
}

void Doodle::UpdateCursorState() {
    try {
        std::cout << "Doodle::UpdateCursorState - Start" << std::endl;

        if (!showWindow) {
            std::cout << "Doodle::UpdateCursorState - Show window is false." << std::endl;
            return;
        }

        if (!window || glfwWindowShouldClose(window)) {
            std::cerr << "Doodle::UpdateCursorState - GLFWwindow pointer is not valid." << std::endl;
            return;
        }

        std::cout << "Before glfwGetWindowAttrib" << std::endl;
        bool isWindowFocused = glfwGetWindowAttrib(window, GLFW_FOCUSED) != 0;
        std::cout << "After glfwGetWindowAttrib" << std::endl;

        // Rest of the method...
    } catch (const std::exception& e) {
        std::cerr << "Exception in Doodle::UpdateCursorState: " << e.what() << std::endl;
    }
}

void Doodle::PreRender() {
    Component::PreRender(); // Call the base class PreRender method
    if (!showWindow || skipRendering) {
        std::cout << "Doodle::PreRender skipped." << std::endl;
        return; // Skip PreRender if not showing or rendering is to be skipped
    }

    if (!showWindow) {
        skipRendering = true;
        return;
    }

    skipRendering = false;

    if (firstRender) {
        std::cout << "Setting initial window size and position." << std::endl;
        ImGui::SetNextWindowSize(ImVec2(300, 300)); // Set size
        ImGui::SetNextWindowPos(initialPos); // Set position
        firstRender = false;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    std::string windowTitle = "Doodle " + std::to_string(id);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_TitleBarMove | ImGuiWindowFlags_NoScrollbar;

    // Ensuring ImGui window creation is successful
    if (!ImGui::Begin(windowTitle.c_str(), &showWindow, window_flags)) {
        std::cerr << "ImGui::Begin failed for Doodle." << std::endl;
        showWindow = false; // Consider closing the window in case of failure
        return;
    }
}

void Doodle::Update() {
    std::cout << "Doodle::Update - Start" << std::endl;

    if (!IsVisible() || !window) {
        std::cout << "Doodle::Update - Skipped (Not visible or window is null)" << std::endl;
        return;
    }

    std::cout << "Doodle::Update - PING" << std::endl;

    try {
        UpdateCursorState();

        if (showWindow) {
            std::cout << "Doodle::Update - showWindow is true" << std::endl;
            PreRender();
            std::cout << "Doodle::Update - After PreRender" << std::endl;
            RenderCanvas();
            std::cout << "Doodle::Update - After RenderCanvas" << std::endl;
            RenderContextMenu();
            std::cout << "Doodle::Update - After RenderContextMenu" << std::endl;
            PostRender();
            std::cout << "Doodle::Update - After PostRender" << std::endl;
        } else {
            std::cout << "Doodle window is not shown. Skipping render." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception in Doodle::Update: " << e.what() << std::endl;
    }

    std::cout << "Doodle::Update - End" << std::endl;
}


void Doodle::RenderCanvas() { // Render Canvas

    //render canvas console ping
    std::cout << "Doodle::RenderCanvas PING" << std::endl;

    // Get the size of the entire window for the canvas
    ImVec2 canvasSize = ImGui::GetWindowSize();

    // If the size is greater than 0, render the canvas
    if (canvasSize.x > 0 && canvasSize.y > 0) {
        ImVec2 canvasMin = ImGui::GetWindowPos();
        ImVec2 canvasMax = ImVec2(canvasMin.x + canvasSize.x, canvasMin.y + canvasSize.y);

        // Fill the canvas with the selected color
        ImGui::GetWindowDrawList()->AddRectFilled(canvasMin, canvasMax, this->canvasColor);

        // Create an invisible button over the canvas to handle drawing
        ImGui::InvisibleButton("canvas", canvasSize);
    }

    // Handle drawing
    HandleDrawing();

    // Debug print statement after HandleDrawing
    std::cout << "Doodle::RenderCanvas - HandleDrawing completed" << std::endl;
}

void Doodle::RenderContextMenu() {
    // context menu console ping
    std::cout << "Doodle::RenderContextMenu PING" << std::endl;

    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1, false)) {
        std::cout << "Window is hovered and right mouse button clicked" << std::endl;
        ImGui::OpenPopup("ContextMenu");
    }

    if (ImGui::BeginPopup("ContextMenu")) {
        std::cout << "BeginPopup 'ContextMenu' returned true" << std::endl;
        RenderModeMenuItems();
        RenderClearCanvasButton();
        RenderSizeSection();
        RenderColorSection();
        RenderCloseButton();
        ImGui::EndPopup();
    } else {
        std::cout << "BeginPopup 'ContextMenu' returned false" << std::endl;
    }
}

void Doodle::RenderModeMenuItems() {
    // mode menu items console ping
    std::cout << "Doodle::RenderModeMenuItems PING" << std::endl;
    const char* menuItemLabel = chalkboardMode ? "Paper" : "Chalkboard";
    if (ImGui::MenuItem(menuItemLabel)) {
        ToggleChalkboardMode();
    }
    ImGui::Separator();

    if (ImGui::MenuItem(eraseMode ? "Draw" : "Erase")) {
        eraseMode = !eraseMode;
        GLFWcursor* newCursor = eraseMode ? eraseCursor : pencilCursor;
        UpdateCursor(newCursor);
    }
    ImGui::Separator();
}

void Doodle::RenderClearCanvasButton() {
    // clear canvas button console ping
    std::cout << "Doodle::RenderClearCanvasButton PING" << std::endl;
    if (ImGui::Button("Clear")) {
        // Clear the canvas
        strokes.clear();
    }
}

void Doodle::RenderSizeSection() {
    // size section console ping
    std::cout << "Doodle::RenderSizeSection PING" << std::endl;
    // Assuming you have a variable `lineThickness` for the line thickness
    ImGui::Text("Line Thickness");
    ImGui::SliderFloat("", &lineThickness, 1.0f, 10.0f);
}

void Doodle::RenderColorSection() {
    // color section console ping
    std::cout << "Doodle::RenderColorSection PING" << std::endl;
    // Assuming you have a variable `lineColor` for the line color
    ImGui::Text("Line Color");
    ImGui::ColorEdit3("", (float*)&lineColor);
}

void Doodle::RenderCloseButton() {
    // close button console ping
    std::cout << "Doodle::RenderCloseButton PING" << std::endl;
    if (ImGui::Button("Close")) {
        showWindow = false;
    }
}

void Doodle::ToggleChalkboardMode() { // Toggle Chalkboard Mode/Paper Mode
    this->chalkboardMode = !this->chalkboardMode;
    // Update canvasColor and lineColor based on the mode
    this->canvasColor = this->chalkboardMode ? IM_COL32(6, 26, 17, 255) : IM_COL32(245, 245, 220, 255);
    this->lineColor = this->chalkboardMode ? IM_COL32(255, 255, 255, 255) : IM_COL32(0, 0, 0, 255);
}
void Doodle::HandleDrawing() {
    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 itemRectMin = ImGui::GetItemRectMin();
    ImVec2 canvasPos = ImVec2(mousePos.x - itemRectMin.x, mousePos.y - itemRectMin.y);

    bool cursorUpdated = false;

    if (ImGui::IsWindowFocused() && ImGui::IsItemHovered()) {
        GLFWcursor* newCursor = eraseMode ? eraseCursor : pencilCursor;

        if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
            glfwSetCursor(window, newCursor);
            cursorUpdated = true;

            if (ImGui::GetIO().KeyShift) {
                if (!isDrawingStraightLine) {
                    straightLineStart = canvasPos;
                    isDrawingStraightLine = true;
                }
            } else if (eraseMode) {
                EraseLines(canvasPos);
            } else {
                AddPointToStroke(canvasPos);
            }
        } else if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            if (isDrawingStraightLine) {
                AddPointToStroke(straightLineStart);
                AddPointToStroke(canvasPos);
                isDrawingStraightLine = false;
                cursorUpdated = true;
            }
            isDrawing = false;
        }
    }

    DrawLines(itemRectMin);

    if (cursorUpdated) {
        UpdateCursorState();
    }
}
void Doodle::AddPointToStroke(const ImVec2& point) { // Add Point to Stroke
    std::cout << "Adding point to stroke: " << point.x << ", " << point.y << std::endl;
    if (!isDrawing) {
        strokes.push_back(std::vector<ImVec2>());
        isDrawing = true;
    }
    strokes.back().push_back(point);
}
void Doodle::DrawLines(ImVec2 itemRectMin) { // Draw Lines
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    for (const auto& stroke : strokes) {
        for (size_t i = 1; i < stroke.size(); ++i) {
            ImVec2 p1 = ImVec2(stroke[i - 1].x + itemRectMin.x, stroke[i - 1].y + itemRectMin.y);
            ImVec2 p2 = ImVec2(stroke[i].x + itemRectMin.x, stroke[i].y + itemRectMin.y);
            draw_list->AddLine(p1, p2, lineColor, 1.0f);
        }
    }
}
void Doodle::EraseLines(const ImVec2& eraseCenter) { // Erase Lines
    float eraseBoxSize = 10.0f;

    std::vector<std::vector<ImVec2>> newStrokes;

    for (auto& stroke : strokes) {
        std::vector<ImVec2> newStroke;
        for (const auto& p : stroke) {
            if (std::abs(p.x - eraseCenter.x) > eraseBoxSize / 2 ||
                std::abs(p.y - eraseCenter.y) > eraseBoxSize / 2) {
                newStroke.push_back(p);
            } else if (!newStroke.empty()) {
                newStrokes.push_back(newStroke);
                newStroke.clear();
            }
        }
        if (!newStroke.empty()) {
            newStrokes.push_back(newStroke);
        }
    }

    strokes.swap(newStrokes);
}
void Doodle::PostRender() { // Post Render
    // post render console ping
    std::cout << "Doodle::PostRender PING" << std::endl;
    Component::PostRender();
    // component post render console ping
    std::cout << "Component::PostRender PING" << std::endl;
    ImGui::End();
    ImGui::PopStyleVar();
}
GLFWwindow* Doodle::GetWindow() { // Get Window
    return window;
}
void Doodle::SetWindow(GLFWwindow* win) { // Set Window
    window = win;
}
