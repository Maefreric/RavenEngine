#include "Doodle.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/stb/stb_image.h"

int Doodle::nextID = 0; // Initialize static ID counter

Doodle::Doodle(int x, int y, Workspace& workspace, GLFWwindow* win)
    : Component(x, y, workspace), window(win), id(nextID++) {
    int cursorWidth, cursorHeight, cursorChannels;

    // Load pencil cursor
    unsigned char* cursorPixels = stbi_load("../Components/Doodle/Assets/pencil.png",
                                            &cursorWidth, &cursorHeight, &cursorChannels, 4);
    if (cursorPixels) {
        GLFWimage cursorImage{cursorWidth, cursorHeight, cursorPixels};
        customCursor = glfwCreateCursor(&cursorImage, 0, 0);
        stbi_image_free(cursorPixels);
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    }

    // Load eraser cursor
    unsigned char* eraseCursorPixels = stbi_load("../Components/Doodle/Assets/eraser.png",
                                                 &cursorWidth, &cursorHeight, &cursorChannels, 4);
    if (eraseCursorPixels) {
        GLFWimage eraseCursorImage{cursorWidth, cursorHeight, eraseCursorPixels};
        eraseCursor = glfwCreateCursor(&eraseCursorImage, cursorWidth / 2, cursorHeight / 2);
        stbi_image_free(eraseCursorPixels);
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

    // Start the ImGui frame
    ImGui::Begin(windowTitle.c_str(), &showWindow, window_flags);
    return true;
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

    UpdateCursor(desiredCursor); // Use the UpdateCursor method here
}

void Doodle::Render() {
    if (!PreRender()) {// If PreRender returns false, skip rendering
        return; 
    }
    if (ImGui::IsItemClicked()) { // Set window focus when clicked
        ImGui::SetWindowFocus();
    }
    UpdateCursorState();
    RenderContextMenu();
    RenderCanvas();
    HandleDrawing();
    PostRender();
}

void Doodle::RenderContextMenu(){// Render Right-click Menu
    // Right-click to open the context menu
    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1, false)) {
        ImGui::OpenPopup("ContextMenu");
    }
    if (ImGui::BeginPopup("ContextMenu")) {

        // Toggle chalkboard mode/paper mode
        const char* menuItemLabel = chalkboardMode ? "Paper" : "Chalkboard";
        if (ImGui::MenuItem(menuItemLabel)) {
            ToggleChalkboardMode();
        }
        ImGui::Separator(); // ########################################
        // Toggle draw/erase mode
        if (ImGui::MenuItem(eraseMode ? "Draw" : "Erase")) {
            eraseMode = !eraseMode;
            GLFWcursor* newCursor = eraseMode ? eraseCursor : customCursor;
            UpdateCursor(newCursor);
        }
        // ########################################
        // When the user clicks "Clear", manually draw an overlay and open the modal popup
        if (ImGui::Button("Clear")) {
            // Calculate the overlay size and position based on the Doodle window
            ImVec2 overlay_min = ImGui::GetWindowPos();
            ImVec2 overlay_max = ImVec2(overlay_min.x + ImGui::GetWindowContentRegionMax().x,
                                        overlay_min.y + ImGui::GetWindowContentRegionMax().y);

            // Draw a semi-transparent rectangle over the Doodle window's area
            ImGui::GetWindowDrawList()->AddRectFilled(overlay_min, overlay_max, IM_COL32(128, 128, 128, 128));
            // Open the modal and set its position and size relative to the Doodle window
            ImGui::SetNextWindowPos(overlay_min);
            ImGui::SetNextWindowSize(ImVec2(ImGui::GetWindowContentRegionMax().x, ImGui::GetWindowHeight()));
            ImGui::OpenPopup("Clear Canvas?");
        }
        // Define the modal popup
        if (ImGui::BeginPopupModal("Clear Canvas?", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
            // Get the width of the modal to center the text
            float modal_width = ImGui::GetWindowSize().x;
            
            // Get the text size
            const char* text = "Do you want to clear the canvas?";
            ImVec2 text_size = ImGui::CalcTextSize(text);
            
            // Calculate the position to center the text and set the cursor position
            ImGui::SetCursorPosX((modal_width - text_size.x) * 0.5f);
            ImGui::TextWrapped(text);

            ImGui::Spacing(); // Extra space before buttons

            // Calculate button width for equal sizing and alignment
            float buttonWidth = (modal_width - ImGui::GetStyle().ItemSpacing.x) * 0.5f;
            
            // Center the buttons by setting the cursor position
            ImGui::SetCursorPosX((modal_width - 2 * buttonWidth - ImGui::GetStyle().ItemSpacing.x) * 0.5f);
            
            if (ImGui::Button("Yes", ImVec2(buttonWidth, 0))) {
                strokes.clear();
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();

            if (ImGui::Button("No", ImVec2(buttonWidth, 0))) {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
        ImGui::Separator(); // ########################################
        // Size section
        // Get the aspect ratio of the canvas
        float aspectRatio = canvasSize.x / canvasSize.y;
        ImGuiWindowFlags window_flags = 0; // or initialize with appropriate flags
        // Title for the size section
        ImGui::Text("Size");
        // Display the current canvas size
        ImGui::Text("Current size: %.1f x %.1f", canvasSize.x, canvasSize.y);
        // Use sliders to adjust the canvas size
        static bool lockAspectRatio = false;
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
        // Toggle button for aspect ratio
        ImGui::Checkbox("Lock Ratio", &lockAspectRatio);
        ImGui::Separator(); // ########################################
        // Color section
        // Title for the color section
        ImGui::Text("Custom Color");
        // color picker for the canvas
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
        // ########################################
        // color picker for the line
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
        // ########################################
        ImGui::Separator(); // ########################################
        // close button
        if (ImGui::Button("Close")) {
            showWindow = false;
        }
        ImGui::EndPopup();
    }
}

void Doodle::RenderCanvas() { // Render Canvas
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
}

void Doodle::ToggleChalkboardMode() { // Toggle Chalkboard Mode/Paper Mode
    this->chalkboardMode = !this->chalkboardMode;
    // Update canvasColor and lineColor based on the mode
    this->canvasColor = this->chalkboardMode ? IM_COL32(6, 26, 17, 255) : IM_COL32(245, 245, 220, 255);
    this->lineColor = this->chalkboardMode ? IM_COL32(255, 255, 255, 255) : IM_COL32(0, 0, 0, 255);
}

void Doodle::HandleDrawing() { // Handle Drawing
    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 itemRectMin = ImGui::GetItemRectMin();
    ImVec2 canvasPos = ImVec2(mousePos.x - itemRectMin.x, mousePos.y - itemRectMin.y);
    bool cursorUpdated = false; // Variable to track if the cursor was updated

    if (ImGui::IsWindowFocused() && ImGui::IsItemHovered()) {
        std::cout << "Window is focused and item is hovered" << std::endl;
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
    ImGui::End();
    ImGui::PopStyleVar();
}

GLFWwindow* Doodle::GetWindow() { // Get Window
    return window;
}

void Doodle::SetWindow(GLFWwindow* win) { // Set Window
    window = win;
}

void Doodle::Close() { // Close
    showWindow = false;
}