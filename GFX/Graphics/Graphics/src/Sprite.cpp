#include "GFX/Graphics/Graphics/include/Sprite.h"

namespace GFX::Graphics
{
    Sprite::Sprite(TexturePtr texture)
    {
        setTexture(std::move(texture));
    }

    Sprite::Sprite(TexturePtr texture, ShaderPtr shader) : _shader(std::move(shader))
    {
        setTexture(std::move(texture));
    }

    void Sprite::setTexture(TexturePtr texture, const bool resetRect)
    {
        _texture = std::move(texture);
        if (resetRect)
            resetTextureRect();
    }

    void Sprite::setTextureRect(const TextureRect& rect)
    {
        _textureRect = rect;
        setLocalBounds(glm::vec3(0.0f), glm::vec3(rect.width, rect.height, 0.0f));

        if (!_originManuallySet)
            setOrigin(0.0f, 0.0f, 0.0f);
    }

    void Sprite::resetTextureRect()
    {
        if (!_texture)
        {
            _textureRect = {};
            setLocalBounds(glm::vec3(0.0f), glm::vec3(0.0f));
            return;
        }

        setTextureRect({ 0.0f, 0.0f, static_cast<float>(_texture->getWidth()),
                         static_cast<float>(_texture->getHeight()) });
    }
} // namespace GFX::Graphics
