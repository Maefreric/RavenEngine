#include "Doodle.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/stb/stb_image.h"

int Doodle::nextID = 0; // Initialize static ID counter

Doodle::Doodle(GLFWwindow* win) : id(nextID++), canvasSize(200, 200), customCursor(nullptr), window(win), showWindow(true) {
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

void Doodle::Render() {
    if (!showWindow) {
        return;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    std::string windowTitle = "Doodle " + std::to_string(id);

        // Set the next window size
    ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);
    
    if (!ImGui::Begin(windowTitle.c_str(), &showWindow, ImGuiWindowFlags_NoCollapse)) {
        ImGui::End();
        ImGui::PopStyleVar();
        return;
    }

    ImVec2 availableSize = ImGui::GetContentRegionAvail();
    if (availableSize.x > 0 && availableSize.y > 0) {
        ImGui::InvisibleButton("canvas", availableSize);
        if (ImGui::IsItemHovered() && customCursor) {
            glfwSetCursor(window, customCursor);
        } else {
            glfwSetCursor(window, NULL);
        }

        ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 240, 255));
        HandleDrawing();
    }

    ImGui::End();
    ImGui::PopStyleVar();
}

void Doodle::HandleDrawing() {
    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 itemRectMin = ImGui::GetItemRectMin();
    ImVec2 canvasPos = ImVec2(mousePos.x - itemRectMin.x, mousePos.y - itemRectMin.y);

    if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && ImGui::GetIO().KeyShift) {
        if (!strokes.empty()) {
            strokes.back().push_back(canvasPos);
        }
    } else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !ImGui::GetIO().KeyShift) {
        strokes.push_back(std::vector<ImVec2>{canvasPos});
    }

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
