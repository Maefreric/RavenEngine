#ifndef COMPONENTS_H
#define COMPONENTS_H

class Workspace;  // Forward declaration of Workspace

class Component {
public:
    Component(int x, int y, Workspace& workspace);
    virtual ~Component() = default;

    virtual void Render() = 0; // Pure virtual function for rendering
    virtual void Update() = 0; // Pure virtual function for updating

    bool IsVisible() const;
    void SetVisibility(bool visible);

    int GetX() const;
    int GetY() const;

protected:
    int x, y;
    bool visible;
    Workspace& workspace;
};

#endif // COMPONENTS_H