#include "Components.h"
#include <iostream>


Component::Component(float x, float y, float width, float height, Workspace& workspace, GLFWwindow* win)
    : x(x), y(y), width(width), height(height), workspace(workspace), window(win), visible(true) {}

Component::~Component() {
    // Any cleanup code for Component goes here
}

bool Component::IsVisible() const {
    return visible;
}

std::string Component::GetName() const {
    return "ComponentName"; // Should be overridden in derived classes
}

void Component::SetVisibility(bool visible) {
    this->visible = visible;
}

float Component::GetX() const {
    return x;
}

float Component::GetY() const {
    return y;
}

float Component::GetWidth() const {
    return width;
}

float Component::GetHeight() const {
    return height;
}

void Component::PreRender() {
}

void Component::Render() {
}

void Component::PostRender() {
}

void Component::Update() {
    if (!IsVisible()) {
        std::cout << GetName() << " is not visible." << std::endl;
        return;
    }
    PreRender();
    Render();
    PostRender();
}
