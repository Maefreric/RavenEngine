#include "Renderer/Primitives/Point.h"

namespace RavenEngine {

Point::Point(float x, float y, float z) : x(x), y(y), z(z), VAO(0), VBO(0) {}

Point::~Point() {
    // Cleanup VAO and VBO
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Point::Create() {
    // Setup VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3, &this->x, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Point::Render() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 1);
    glBindVertexArray(0);
}

void Point::setupPoint() {
    // The logic from Create method can be moved here if needed
}

} // namespace RavenEngine
