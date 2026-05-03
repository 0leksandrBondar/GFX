#include "GFX/Graphics/Graphics/include/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_ONLY_PNG
#include "GFX/Graphics/Graphics/include/Texture.h"

#include "GFX/Graphics/RawGraphics/include/stb_image.h"
#include "spdlog/spdlog.h"

namespace GFX::Graphics
{
    Texture::Texture(const std::filesystem::path& path) { loadTexture(path); }

    TexturePtr Texture::create(const std::filesystem::path& path)
    {
        return std::make_shared<Texture>(path);
    }

    void Texture::loadTexture(const std::filesystem::path& path)
    {
        unsigned char* pixels
            = stbi_load(path.string().c_str(), &_width, &_height, &channels, STBI_rgb_alpha);

        if (!pixels)
            throw std::runtime_error(stbi_failure_reason());

        _raw = RawTexture::create(_width, _height, pixels, channels);
        //_rect = { 0, 0, static_cast<float>(_width), static_cast<float>(_height) };

        stbi_image_free(pixels);
    }

    void Texture::setSmooth(const bool smooth)
    {
        _isSmooth = smooth;
        _raw->setSmooth(smooth);
    }

} // namespace GFX::Graphics