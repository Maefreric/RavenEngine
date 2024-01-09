#ifndef FILE_DIALOG_H
#define FILE_DIALOG_H

#include <GLFW/glfw3.h>
#include <string>

class FileDialog {
public:
    static std::string OpenFileDialog(GLFWwindow* ownerWindow);
};

#endif // FILE_DIALOG_H
