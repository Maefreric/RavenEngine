#ifndef WORKSPACE_H
#define WORKSPACE_H

class Workspace {
public:
    Workspace(int width, int height, int menuBarHeight); // Add menuBarHeight parameter

    bool isInside(int x, int y);

private:
    int width;
    int height;
    int menuBarHeight; // Add menuBarHeight member variable
};

#endif // WORKSPACE_H