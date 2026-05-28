#include "GFX/Graphics/Graphics/include/Renderer.h"

namespace GFX::Graphics
{
    void Renderer::draw(const Model& model, const Material& material,
                        const Core::Camera& camera) const
    {
        const ShaderPtr& shader = material.getShader();
        if (!shader)
            return;

        material.apply();
        draw(model, *shader, camera);
        material.unuseTextures();
    }

    void Renderer::draw(const Model& model, const Shader& shader, const Core::Camera& camera) const
    {
        shader.use();
        shader.setMatrix4("uModel", model.getModelMatrix());
        shader.setMatrix4("uView", camera.getViewMatrix());
        shader.setMatrix4("uProjection", camera.getProjectionMatrix());
        shader.setVector3("uViewPos", camera.getPosition());

        model.bind();
        glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
    }
} // namespace GFX::Graphics
