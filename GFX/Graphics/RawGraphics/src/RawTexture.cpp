#include "GFX/Graphics/RawGraphics/include/RawTexture.h"

#include "glad/glad.h"

namespace GFX::Graphics
{
    RawTexture::RawTexture(const int width, const int height, const unsigned char* data,
                           const int channels)
    {
        if (!data)
            throw std::runtime_error("RawTexture: data is null");

        GLenum format = GL_RGB;
        if (channels == 4)
            format = GL_RGBA;
        else if (channels == 3)
            format = GL_RGB;
        else if (channels == 1)
            format = GL_RED;
        else
            throw std::runtime_error("RawTexture: unsupported channel count");

        glGenTextures(1, &_id);
        glBindTexture(GL_TEXTURE_2D, _id);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    std::shared_ptr<RawTexture> RawTexture::create(int width, int height, const unsigned char* data,
                                                   int channels)
    {
        return std::make_shared<RawTexture>(width, height, data, channels);
    }

    void RawTexture::setSmooth(const bool smooth) const
    {
        bind();
        const GLenum filter = smooth ? GL_LINEAR : GL_NEAREST;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

        unbind();
    }
} // namespace gfx2d