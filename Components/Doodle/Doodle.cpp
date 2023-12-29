#include "Doodle.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <chrono>

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

    // Load eraser cursor
    unsigned char* eraseCursorPixels = stbi_load("../Components/Doodle/Assets/eraser.png",
                                                 &cursorWidth, &cursorHeight, &cursorChannels, 4);
    if (eraseCursorPixels) {
        GLFWimage eraseCursorImage{cursorWidth, cursorHeight, eraseCursorPixels};
        eraseCursor = glfwCreateCursor(&eraseCursorImage, cursorWidth / 2, cursorHeight / 2);
        stbi_image_free(eraseCursorPixels);
    } else {
        std::cerr << "Failed to load eraser cursor image" << std::endl;
    }
}

Doodle::~Doodle() {
    if (customCursor) {
        glfwDestroyCursor(customCursor);
    }
    if (eraseCursor) {
        glfwDestroyCursor(eraseCursor);
    }
}

void Doodle::SetPosition(const ImVec2& pos) {
    initialPos = pos;
    firstRender = true;
}

// Store the last time you logged
std::chrono::steady_clock::time_point lastLogTime;

bool Doodle::PreRender() {
    if (!showWindow) {
        return false;
    }

    if (firstRender) {
        ImGui::SetNextWindowSize(ImVec2(300, 300)); // Consistent window size
        ImGui::SetNextWindowPos(initialPos); // Initial window position
        firstRender = false;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    std::string windowTitle = "Doodle " + std::to_string(id);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_TitleBarMove | ImGuiWindowFlags_NoScrollbar;

    // Get the current time
    auto now = std::chrono::steady_clock::now();

    // Check if at least 15 seconds have passed since the last log
    if (std::chrono::duration_cast<std::chrono::seconds>(now - lastLogTime).count() >= 15) {
        // Log the window flags
        std::cout << "Current window flags before ImGui::Begin: " << window_flags << std::endl;

        // Update the last log time
        lastLogTime = now;
    }

    // Start the ImGui frame
    ImGui::Begin(windowTitle.c_str(), &showWindow, window_flags);

    return true; // Add this line
}

void Doodle::UpdateCursor(GLFWcursor* desiredCursor) {
    if (currentCursor != desiredCursor) {
        glfwSetCursor(window, desiredCursor);
        currentCursor = desiredCursor;
    }
}

void Doodle::UpdateCursorState() {
    if (!showWindow) return;

    bool isWindowFocused = glfwGetWindowAttrib(window, GLFW_FOCUSED) != 0;
    bool isWindowHovered = ImGui::IsWindowHovered();

    GLFWcursor* desiredCursor = nullptr;
    if (isWindowFocused && isWindowHovered) {
        desiredCursor = eraseMode ? eraseCursor : customCursor;
    }

    if (currentCursor != desiredCursor) {
        glfwSetCursor(window, desiredCursor);
        currentCursor = desiredCursor;
    }
}


void Doodle::Render() {
    UpdateCursorState(); // First call

    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1, false)) {
        ImGui::OpenPopup("ContextMenu");
    }

    if (ImGui::BeginPopup("ContextMenu")) {
        const char* menuItemLabel = chalkboardMode ? "Paper" : "Chalkboard";
        if (ImGui::MenuItem(menuItemLabel)) {
            ToggleChalkboardMode();
        }
        
        ImGui::Separator();

        if (ImGui::MenuItem(eraseMode ? "Draw" : "Erase")) {
            eraseMode = !eraseMode;
            GLFWcursor* newCursor = eraseMode ? eraseCursor : customCursor;
            UpdateCursor(newCursor);
        }

        ImGui::Separator();
        
        // Declare aspectRatio and window_flags
        float aspectRatio = canvasSize.x / canvasSize.y;
        ImGuiWindowFlags window_flags = 0; // or initialize with appropriate flags

        // Size section
        ImGui::Text("Size");

        // Display the current canvas size
        ImGui::Text("Current size: %.1f x %.1f", canvasSize.x, canvasSize.y);

        // Use sliders to adjust the canvas size
        static bool lockAspectRatio = false;
        static bool noResize = false;
        bool widthChanged = ImGui::SliderFloat("Width", &canvasSize.x, 20.0f, 1800.0f);
        bool heightChanged = ImGui::SliderFloat("Height", &canvasSize.y, 20.0f, 1100.0f);

        // If the aspect ratio is locked and one of the dimensions changed, adjust the other dimension
        if (lockAspectRatio && (widthChanged || heightChanged)) {
            if (widthChanged) {
                canvasSize.y = canvasSize.x / aspectRatio;
            } else if (heightChanged) {
                canvasSize.x = canvasSize.y * aspectRatio;
            }
        }

        // If the size changed, apply the changes to the ImGui window and canvas
        if (widthChanged || heightChanged) {
            // Apply the size changes to the ImGui window
            ImGui::SetWindowSize(("Doodle " + std::to_string(id)).c_str(), ImVec2(canvasSize.x, canvasSize.y));
        }

        // Toggle buttons for aspect ratio locking and disabling resizing
        ImGui::Checkbox("Lock Ratio", &lockAspectRatio);
        if (ImGui::Checkbox("Disable Resizing", &noResize)) {
            std::cout << "Disable Resizing toggled: " << (noResize ? "ON" : "OFF") << std::endl; // Debug message 1
            if (noResize) {
                window_flags |= ImGuiWindowFlags_NoResize;
            } else {
                window_flags &= ~ImGuiWindowFlags_NoResize;
            }
            std::cout << "Window flags updated: " << window_flags << std::endl; // Debug message 2
        }

        ImGui::Separator();

        // Color section
        ImGui::Text("Color");
        if (ImGui::ColorEdit4("##Background", (float*)&this->UserCustomBGColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel)) {
            std::cout << "Selected Canvas color: (" 
                      << this->UserCustomBGColor.x << ", " 
                      << this->UserCustomBGColor.y << ", " 
                      << this->UserCustomBGColor.z << ", " 
                      << this->UserCustomBGColor.w << ")" << std::endl;
            // Update the canvas color
            this->canvasColor = ImGui::ColorConvertFloat4ToU32(this->UserCustomBGColor);
        }
        ImGui::SameLine();
        ImGui::Text("Canvas");

        if (ImGui::ColorEdit4("##Line", (float*)&this->UserCustomLineColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel)) {
            std::cout << "Selected line color: (" 
                      << this->UserCustomLineColor.x << ", " 
                      << this->UserCustomLineColor.y << ", " 
                      << this->UserCustomLineColor.z << ", " 
                      << this->UserCustomLineColor.w << ")" << std::endl;
            // Update the line color
            this->lineColor = ImGui::ColorConvertFloat4ToU32(this->UserCustomLineColor);
        }
        ImGui::SameLine();
        ImGui::Text("Line");

        ImGui::Separator();

        // clear button
        if (ImGui::Button("Clear")) {
            strokes.clear();
        }

        ImGui::EndPopup();
    }

    // Use the color and size variables to modify the drawing behavior
    ImVec2 availableSize = ImGui::GetContentRegionAvail();
    if (availableSize.x > 0 && availableSize.y > 0) {
        ImGui::InvisibleButton("canvas", availableSize);
        ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), this->canvasColor);
        HandleDrawing();
    }

    if (ImGui::IsItemClicked()) {
        ImGui::SetWindowFocus();
    }
    
    if (!PreRender()) {
        return;
    }

    PostRender();
}

void Doodle::ToggleChalkboardMode() {
    this->chalkboardMode = !this->chalkboardMode;
    // Update canvasColor and lineColor based on the mode
    this->canvasColor = this->chalkboardMode ? IM_COL32(6, 26, 17, 255) : IM_COL32(245, 245, 220, 255);
    this->lineColor = this->chalkboardMode ? IM_COL32(255, 255, 255, 255) : IM_COL32(0, 0, 0, 255);
}

void Doodle::PostRender() {
    ImGui::End();
    ImGui::PopStyleVar();
}

void Doodle::HandleDrawing() {
    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 itemRectMin = ImGui::GetItemRectMin();
    ImVec2 canvasPos = ImVec2(mousePos.x - itemRectMin.x, mousePos.y - itemRectMin.y);
    bool cursorUpdated = false; // Variable to track if the cursor was updated

    if (ImGui::IsWindowFocused() && ImGui::IsItemHovered()) {
        GLFWcursor* newCursor = eraseMode ? eraseCursor : customCursor;

        if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
            glfwSetCursor(window, newCursor); // Explicitly set cursor on mouse down
            cursorUpdated = true; // Mark that the cursor was updated

            if (ImGui::GetIO().KeyShift) {
                if (!isDrawingStraightLine) {
                    straightLineStart = canvasPos;
                    isDrawingStraightLine = true;
                } // Don't add points yet
            } else if (eraseMode) {
                EraseLines(canvasPos);
            } else {
                AddPointToStroke(canvasPos);
            }
        } else if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            if (isDrawingStraightLine) {
                // Now add the points for the straight line
                AddPointToStroke(straightLineStart);
                AddPointToStroke(canvasPos);
                isDrawingStraightLine = false;
                cursorUpdated = true; // Mark that the cursor was updated
            }
            isDrawing = false;
        }
    }

    DrawLines(itemRectMin);

    // Update the cursor state if it was changed during mouse events
    if (cursorUpdated) {
        UpdateCursorState();
    }
}

void Doodle::AddPointToStroke(const ImVec2& point) {
    if (!isDrawing) {
        strokes.push_back(std::vector<ImVec2>());
        isDrawing = true;
    }
    strokes.back().push_back(point);
}

void Doodle::DrawLines(ImVec2 itemRectMin) {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    for (const auto& stroke : strokes) {
        for (size_t i = 1; i < stroke.size(); ++i) {
            ImVec2 p1 = ImVec2(stroke[i - 1].x + itemRectMin.x, stroke[i - 1].y + itemRectMin.y);
            ImVec2 p2 = ImVec2(stroke[i].x + itemRectMin.x, stroke[i].y + itemRectMin.y);
            draw_list->AddLine(p1, p2, lineColor, 1.0f);
        }
    }
}

void Doodle::EraseLines(const ImVec2& eraseCenter) {
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

void Doodle::Close() {
    showWindow = false;
}

GLFWwindow* Doodle::GetWindow() {
    return window;
}

void Doodle::SetWindow(GLFWwindow* win) {
    window = win;
}