#include "GFX/Graphics/Graphics/include/RenderContext.h"

namespace GFX::Graphics
{
    void RenderContext::clear(const Color& color) const
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderContext::draw(const Model& model, const Material& material,
                             const Core::Camera& camera) const
    {
        _modelRenderer.draw(model, material, camera);
    }

    void RenderContext::draw(const Model& model, const Shader& shader,
                             const Core::Camera& camera) const
    {
        _modelRenderer.draw(model, shader, camera);
    }

    void RenderContext::draw(const Sprite& sprite, const Core::Camera& camera)
    {
        _spriteRenderer.draw(sprite, camera);
    }

    void RenderContext::draw(const Text& text, const Core::Camera& camera)
    {
        _textRenderer.draw(text, camera);
    }
} // namespace GFX::Graphics
