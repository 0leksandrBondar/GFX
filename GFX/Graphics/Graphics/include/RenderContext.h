#pragma once

#include "GFX/Core/Camera/include/Camera.h"
#include "GFX/Graphics/Graphics/include/Material.h"
#include "GFX/Graphics/Graphics/include/Model.h"
#include "GFX/Graphics/Graphics/include/Renderer.h"
#include "GFX/Graphics/Graphics/include/Sprite.h"
#include "GFX/Graphics/Graphics/include/SpriteRenderer.h"
#include "GFX/Graphics/Graphics/include/Text.h"
#include "GFX/Graphics/Graphics/include/TextRenderer.h"
#include "GFX/Graphics/RawGraphics/include/Shader.h"

#include <utility>

namespace GFX::Graphics
{
    class RenderContext final : public Core::NonCopyableButMovable
    {
    public:
        RenderContext() = default;

        void clear(const Color& color = Colors::Black) const;
        void draw(const Model& model, const Material& material, const Core::Camera& camera) const;
        void draw(const Model& model, const Shader& shader, const Core::Camera& camera) const;
        void draw(const Sprite& sprite, const Core::Camera& camera);
        void draw(const Text& text, const Core::Camera& camera);

        [[nodiscard]] SpriteRenderer& getSpriteRenderer() { return _spriteRenderer; }
        [[nodiscard]] const SpriteRenderer& getSpriteRenderer() const { return _spriteRenderer; }
        [[nodiscard]] TextRenderer& getTextRenderer() { return _textRenderer; }
        [[nodiscard]] const TextRenderer& getTextRenderer() const { return _textRenderer; }
        void setDefaultSpriteShader(ShaderPtr shader) { _spriteRenderer.setDefaultShader(std::move(shader)); }
        void setDefaultTextShader(ShaderPtr shader) { _textRenderer.setDefaultShader(std::move(shader)); }

    private:
        Renderer _modelRenderer;
        SpriteRenderer _spriteRenderer;
        TextRenderer _textRenderer;
    };
} // namespace GFX::Graphics
