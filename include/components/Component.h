#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <imgui.h>

class Component {
protected:
    float x, y, width, height;
    bool visible;
    std::string name;

public:
    Component() : x(0.0f), y(0.0f), width(0.0f), height(0.0f), visible(false), name("") {}
    Component(float x, float y, float width, float height, const std::string& name);
    virtual ~Component() = default;

    virtual void Update() = 0; // Make Update a pure virtual function
    virtual void RenderImGui() = 0; // Already a pure virtual function for ImGui rendering

    bool IsVisible() const;
    void SetVisibility(bool visible);

    // Getters and setters for position and size if needed
    float GetX() const;
    float GetY() const;
    float GetWidth() const;
    float GetHeight() const;
    void SetPosition(float x, float y);
    void SetSize(float width, float height);

    const std::string& GetName() const;
};

#endif // COMPONENT_H
