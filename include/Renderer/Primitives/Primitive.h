#pragma once

namespace RavenEngine {

enum class PrimitiveType {
    Point,
    Line,
    Triangle
    // Add more types if needed
};

class Primitive {
public:
    Primitive(PrimitiveType type);
    ~Primitive();

    void Create(); // Method to create the primitive data
    void Render(); // Method to render the primitive

private:
    PrimitiveType type;
    unsigned int VAO, VBO; // Vertex Array Object, Vertex Buffer Object
    // Other relevant data (vertex data, etc.)

    void setupPrimitive(); // Setup the VAO and VBO
};

} // namespace RavenEngine
