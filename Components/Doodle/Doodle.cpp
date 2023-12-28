#include "Doodle.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/stb/stb_image.h"

int Doodle::nextID = 0; // Initialize static ID counter

Doodle::Doodle(GLFWwindow* win) : id(nextID++), canvasSize(200, 200), customCursor(nullptr), window(win), showWindow(true), firstRender(true), initialPos(ImVec2(200, 200)) {
    int cursorWidth, cursorHeight, cursorChannels;
    unsigned char* cursorPixels = stbi_load("../Components/Doodle/Assets/pencil.png",
                                            &cursorWidth, &cursorHeight, &cursorChannels, 4);
    if (cursorPixels) {
        GLFWimage cursorImage{cursorWidth, cursorHeight, cursorPixels};
        customCursor = glfwCreateCursor(&cursorImage, 0, 0);
        stbi_image_free(cursorPixels);
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    } else {
        std::cerr << "Failed to load cursor image" << std::endl;
    }
}

Doodle::~Doodle() {
    if (customCursor) {
        glfwDestroyCursor(customCursor);
    }
}

void Doodle::SetPosition(const ImVec2& pos) {
    initialPos = pos;
    firstRender = true;
}

void Doodle::Render() {
    if (!showWindow) {
        return;
    }

    if (firstRender) {
        ImGui::SetNextWindowSize(ImVec2(300, 300)); // Consistent window size
        ImGui::SetNextWindowPos(initialPos); // Initial window position
        firstRender = false;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    std::string windowTitle = "Doodle " + std::to_string(id);

    // Essential window flags for ImGui. Do not remove.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize; 
    if (ImGui::Begin(windowTitle.c_str(), &showWindow, window_flags)) {
        ImVec2 availableSize = ImGui::GetContentRegionAvail();
        if (availableSize.x > 0 && availableSize.y > 0) {
            ImGui::InvisibleButton("canvas", availableSize);
            
            // Set custom cursor for the canvas
            if (ImGui::IsItemHovered() && customCursor) {
                glfwSetCursor(window, customCursor);
            } else {
                glfwSetCursor(window, NULL);
            }

            // Set canvas background color
            ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(245, 245, 220, 255));
            
            // Draw on canvas regardless of window focus
            HandleDrawing();
        }

        // Click to focus
        if (ImGui::IsItemClicked()) {
            ImGui::SetWindowFocus();
        }

        ImGui::End();
    }
    ImGui::PopStyleVar();
}



void Doodle::HandleDrawing() {
    static ImVec2 lastPoint(0.0f, 0.0f); // Holds the last point drawn
    static bool isShiftDown = false; // Flag to check if the shift key is down
    static bool isDrawing = false; // Flag to check if we are currently drawing

    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 itemRectMin = ImGui::GetItemRectMin();
    ImVec2 canvasPos = ImVec2(mousePos.x - itemRectMin.x, mousePos.y - itemRectMin.y);

    // Check for shift key
    isShiftDown = ImGui::GetIO().KeyShift;

    if (ImGui::IsWindowFocused()) {
        if (ImGui::IsMouseDragging(ImGuiMouseButton_Left, 0.0f) && ImGui::IsItemHovered()) {
            if (!isDrawing || strokes.empty() || strokes.back().empty()) {
                // Start a new stroke
                strokes.push_back(std::vector<ImVec2>{canvasPos});
                isDrawing = true; // We started drawing
            } else if (isShiftDown) {
                // If shift is down, draw straight line from the last point
                strokes.back().push_back(lastPoint);
                strokes.back().push_back(canvasPos);
            } else {
                // Continue the last stroke
                strokes.back().push_back(canvasPos);
            }
            lastPoint = canvasPos; // Update the last point
        } else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsItemHovered()) {
            // Start a new stroke with a single point
            strokes.push_back(std::vector<ImVec2>{canvasPos});
            lastPoint = canvasPos; // Update the last point
            isDrawing = true; // We started drawing
        } else if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            // When mouse is released, we stop drawing
            isDrawing = false;
        }
    }

    // Always draw existing strokes
    DrawLines(itemRectMin);
}




void Doodle::DrawLines(ImVec2 itemRectMin) {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    for (const auto& stroke : strokes) {
        for (size_t i = 1; i < stroke.size(); ++i) {
            ImVec2 p1 = ImVec2(stroke[i - 1].x + itemRectMin.x, stroke[i - 1].y + itemRectMin.y);
            ImVec2 p2 = ImVec2(stroke[i].x + itemRectMin.x, stroke[i].y + itemRectMin.y);
            draw_list->AddLine(p1, p2, IM_COL32(0, 0, 0, 255), 1.0f);
        }
    }
}

void Doodle::Close() {
    showWindow = false;
}

GLFWwindow* Doodle::GetWindow() {
    return window;
}

void Doodle::SetWindow(GLFWwindow* win) {
    window = win;
}

