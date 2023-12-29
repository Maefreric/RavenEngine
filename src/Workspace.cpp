// workspace.cpp
#include "Workspace.h"

Workspace::Workspace(int width, int height, int menuBarHeight) : 
    width(width), height(height), menuBarHeight(menuBarHeight) {}

bool Workspace::isInside(int x, int y) {
    return x >= 0 && x < width && y >= menuBarHeight && y < height + menuBarHeight;
}
