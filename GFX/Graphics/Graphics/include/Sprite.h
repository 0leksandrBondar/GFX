#pragma once

#include "ExternalLibs/GLM/glm/vec2.hpp"
#include "GFX/Core/BaseTypes/include/Transformable.h"
#include "GFX/Graphics/Graphics/include/Color.h"
#include "GFX/Graphics/Graphics/include/Texture.h"
#include "GFX/Graphics/RawGraphics/include/Shader.h"

#include <utility>

namespace GFX::Graphics
{
    struct TextureRect
    {
        float left{ 0.0f };
        float top{ 0.0f };
        float width{ 0.0f };
        float height{ 0.0f };
    };

    class Sprite final : public Core::Transformable
    {
    public:
        Sprite() = default;
        explicit Sprite(TexturePtr texture);
        Sprite(TexturePtr texture, ShaderPtr shader);

        void setTexture(TexturePtr texture, bool resetRect = true);
        void setShader(ShaderPtr shader) { _shader = std::move(shader); }
        void setTextureRect(const TextureRect& rect);
        void setColor(const Color& color) { _color = color; }
        void setColor(const glm::vec4& color) { _color = { color.r, color.g, color.b, color.a }; }
        void setOpacity(float opacity) { _color.a = opacity; }

        [[nodiscard]] const TexturePtr& getTexture() const { return _texture; }
        [[nodiscard]] const ShaderPtr& getShader() const { return _shader; }
        [[nodiscard]] const TextureRect& getTextureRect() const { return _textureRect; }
        [[nodiscard]] const Color& getColor() const { return _color; }
        [[nodiscard]] glm::vec2 getLocalSize() const
        {
            return glm::vec2(_textureRect.width, _textureRect.height);
        }

    private:
        void resetTextureRect();

    private:
        TexturePtr _texture{ nullptr };
        ShaderPtr _shader{ nullptr };
        TextureRect _textureRect;
        Color _color{ Colors::White };
    };
} // namespace GFX::Graphics
