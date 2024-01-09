// Standard library headers
#include <Windows.h>
#include <commdlg.h> // Common dialogs like open file
#include <tchar.h>   // For _T macro

// Third-party library headers
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

// Project headers
#include "FileDialog.h"

std::string FileDialog::OpenFileDialog(GLFWwindow* ownerWindow) {
    OPENFILENAME ofn;       // common dialog box structure
    TCHAR szFile[260] = {0}; // buffer for file name
    HWND hwnd = glfwGetWin32Window(ownerWindow); // owner window

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box.
    if (GetOpenFileName(&ofn) == TRUE) {
        // Use ofn.lpstrFile here
        return ofn.lpstrFile;
    }
    
    return ""; // Return empty string if no file was selected
}
