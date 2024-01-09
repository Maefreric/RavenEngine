#include "Component.h"

Component::Component(float x, float y, float width, float height, const std::string& name)
    : x(x), y(y), width(width), height(height), visible(true), name(name) {}

bool Component::IsVisible() const {
    return visible;
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

void Component::SetPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

void Component::SetSize(float newWidth, float newHeight) {
    width = newWidth;
    height = newHeight;
}

const std::string& Component::GetName() const {
    return name;
}

void Component::Update() {
    // Update logic if any
}

void Component::RenderImGui() {
    // To be implemented in derived classes
}
