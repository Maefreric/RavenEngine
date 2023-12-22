#include <iostream>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h> // Necessary for glfwGetWin32Window
#include <Windows.h> // Make sure to include this for Windows API functions
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

// Function to handle key events
void handleKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

// Function to create the main menu bar
void createMainMenu(GLFWwindow* window) {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            // File dropdown options go here
            if (ImGui::MenuItem("New Project")) {
                // TODO: Implement New Project
            }
            if (ImGui::MenuItem("Open")) {
                // TODO: Implement open functionality
            }
            if (ImGui::MenuItem("Save")) {
                // TODO: Implement save functionality
            }
            if (ImGui::MenuItem("Exit")) {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set GLFW window hints
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE); // Open the window maximized

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Raven Engine", nullptr, nullptr);

    // Set minimum window size
    glfwSetWindowSizeLimits(window, 800, 600, GLFW_DONT_CARE, GLFW_DONT_CARE);

    // Set window opacity
    glfwSetWindowOpacity(window, 0.95f);

    // Set key callback function
    glfwSetKeyCallback(window, handleKey);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set the window icon using Windows API FAVICON
    HICON hSmallIcon = (HICON)LoadImage(NULL, "D:\\RavenEngineProject\\RavenEngine\\Assets\\RavenLogoImgs\\raven16x16.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
    HICON hLargeIcon = (HICON)LoadImage(NULL, "D:\\RavenEngineProject\\RavenEngine\\Assets\\RavenLogoImgs\\ravenICO32x32.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    
    HWND hwnd = glfwGetWin32Window(window);
    if (hSmallIcon)
    {
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hSmallIcon);
    }
    if (hLargeIcon)
    {
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hLargeIcon);
    }
    


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Load ImGui settings from an .ini file (if it exists)
    ImGui::LoadIniSettingsFromDisk("imgui_settings.ini");

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 150"; // Or whatever version your system supports
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll for and process events
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create the top menu bar
        createMainMenu(window);

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    // Save ImGui settings to an .ini file
    ImGui::SaveIniSettingsToDisk("imgui_settings.ini");

    // Clean up
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Clean up the icons
    if (hSmallIcon)
    {
        DestroyIcon(hSmallIcon); // Clean up the small icon when we're done with it
    }
    if (hLargeIcon)
    {
        DestroyIcon(hLargeIcon); // Clean up the large icon when we're done with it
    }

    glfwDestroyWindow(window); // Destroy the window
    glfwTerminate(); // Terminate GLFW
    return 0;
}