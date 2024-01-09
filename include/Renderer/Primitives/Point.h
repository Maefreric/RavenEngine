#pragma once

#include <glad/glad.h> // Include OpenGL header

namespace RavenEngine {

class Point {
public:
    Point(float x, float y, float z);
    ~Point();

    void Create(); // Set up the point data
    void Render(); // Render the point

private:
    float x, y, z; // Coordinates of the point
    unsigned int VAO, VBO; // Vertex Array Object, Vertex Buffer Object

    void setupPoint(); // Setup the VAO and VBO
};

} // namespace RavenEngine
