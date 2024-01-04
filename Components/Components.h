#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <GLFW/glfw3.h>
#include <string>

class Workspace; // Forward declaration

class Component {
public:
    Component(float x, float y, float width, float height, Workspace& workspace, GLFWwindow* win);
    virtual ~Component();

    virtual bool IsVisible() const;
    void SetVisibility(bool visible);

    float GetX() const;
    float GetY() const;
    float GetWidth() const;
    float GetHeight() const;
    virtual std::string GetName() const;

    virtual void Update();
    virtual void Render();
    virtual void PreRender();
    virtual void PostRender();

protected:
    Workspace& workspace;

private:
    float x, y, width, height;
    bool visible;
    GLFWwindow* window;
};

#endif // COMPONENTS_H
