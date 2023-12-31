#include "Components.h"

Component::Component(int x, int y, Workspace& workspace) 
    : x(x), y(y), visible(true), workspace(workspace) {}


bool Component::IsVisible() const {
    return visible;
}

void Component::SetVisibility(bool visible) {
    this->visible = visible;
}

int Component::GetX() const {
    return x;
}

int Component::GetY() const {
    return y;
}