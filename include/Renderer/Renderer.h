#ifndef RAVENENGINE_RENDERER_H
#define RAVENENGINE_RENDERER_H

#include <glad/glad.h>

namespace RavenEngine {

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool Initialize(int screenWidth, int screenHeight);
    void Shutdown();

    void BeginScene();
    void EndScene();

    void Clear(const float* clearColor);
    void SetViewport(int x, int y, int width, int height);
    void OnWindowResize(int newWidth, int newHeight);

    GLuint GetRenderedTexture() const;

private:
    int screenWidth, screenHeight;
    GLuint fbo; // Framebuffer object for rendering
    GLuint textureColorbuffer; // Texture to render to

    void createFramebuffer();
    void deleteFramebuffer();
};

} // namespace RavenEngine

#endif // RAVENENGINE_RENDERER_H
