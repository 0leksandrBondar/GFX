#include "GFX/Graphics/Graphics/include/Font.h"

#include "ft2build.h"
#include FT_FREETYPE_H

#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>

namespace GFX::Graphics
{
    namespace
    {
        constexpr int AtlasPadding = 1;

        std::vector<char32_t> buildDefaultGlyphSet()
        {
            std::vector<char32_t> glyphs;
            glyphs.reserve((126 - 32 + 1) + (0x052F - 0x0400 + 1));

            for (char32_t character = 32; character <= 126; ++character)
                glyphs.push_back(character);

            for (char32_t character = 0x0400; character <= 0x052F; ++character)
                glyphs.push_back(character);

            return glyphs;
        }
    } // namespace

    FontPtr Font::create(const std::filesystem::path& path, const unsigned int pixelSize)
    {
        return std::make_shared<Font>(path, pixelSize);
    }

    Font::Font(const std::filesystem::path& path, const unsigned int pixelSize)
        : _pixelSize(pixelSize)
    {
        load(path);
    }

    Font::~Font()
    {
        if (_atlasId != 0)
            glDeleteTextures(1, &_atlasId);
    }

    Font::Font(Font&& other) noexcept
    {
        *this = std::move(other);
    }

    Font& Font::operator=(Font&& other) noexcept
    {
        if (this == &other)
            return *this;

        if (_atlasId != 0)
            glDeleteTextures(1, &_atlasId);

        _glyphs = std::move(other._glyphs);
        _atlasId = other._atlasId;
        _pixelSize = other._pixelSize;
        _atlasWidth = other._atlasWidth;
        _atlasHeight = other._atlasHeight;
        _lineHeight = other._lineHeight;
        _ascender = other._ascender;

        other._atlasId = 0;
        return *this;
    }

    void Font::bind(const unsigned int slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, _atlasId);
    }

    void Font::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    const Glyph* Font::getGlyph(const char32_t character) const
    {
        const auto it = _glyphs.find(character);
        if (it == _glyphs.end())
            return nullptr;

        return &it->second;
    }

    void Font::load(const std::filesystem::path& path)
    {
        FT_Library library{};
        if (FT_Init_FreeType(&library))
            throw std::runtime_error("Font: failed to initialize FreeType");

        FT_Face face{};
        if (FT_New_Face(library, path.string().c_str(), 0, &face))
        {
            FT_Done_FreeType(library);
            throw std::runtime_error("Font: failed to load font " + path.string());
        }

        FT_Set_Pixel_Sizes(face, 0, _pixelSize);
        _lineHeight = static_cast<float>(face->size->metrics.height >> 6);
        _ascender = static_cast<float>(face->size->metrics.ascender >> 6);
        const std::vector<char32_t> glyphSet = buildDefaultGlyphSet();

        int rowWidth = 0;
        int rowHeight = 0;
        _atlasWidth = 0;
        _atlasHeight = 0;

        for (const char32_t character : glyphSet)
        {
            if (FT_Load_Char(face, character, FT_LOAD_RENDER))
                continue;

            const FT_Bitmap& bitmap = face->glyph->bitmap;
            if (rowWidth + static_cast<int>(bitmap.width) + AtlasPadding >= 1024)
            {
                _atlasWidth = std::max(_atlasWidth, rowWidth);
                _atlasHeight += rowHeight + AtlasPadding;
                rowWidth = 0;
                rowHeight = 0;
            }

            rowWidth += static_cast<int>(bitmap.width) + AtlasPadding;
            rowHeight = std::max(rowHeight, static_cast<int>(bitmap.rows));
        }

        _atlasWidth = std::max(_atlasWidth, rowWidth);
        _atlasHeight += rowHeight + AtlasPadding;
        _atlasWidth = std::max(_atlasWidth, 1);
        _atlasHeight = std::max(_atlasHeight, 1);

        std::vector<unsigned char> atlas(static_cast<size_t>(_atlasWidth * _atlasHeight), 0);

        int offsetX = 0;
        int offsetY = 0;
        rowHeight = 0;

        for (const char32_t character : glyphSet)
        {
            if (FT_Load_Char(face, character, FT_LOAD_RENDER))
                continue;

            const FT_GlyphSlot glyphSlot = face->glyph;
            const FT_Bitmap& bitmap = glyphSlot->bitmap;

            if (offsetX + static_cast<int>(bitmap.width) + AtlasPadding >= _atlasWidth)
            {
                offsetY += rowHeight + AtlasPadding;
                offsetX = 0;
                rowHeight = 0;
            }

            for (unsigned int y = 0; y < bitmap.rows; ++y)
            {
                for (unsigned int x = 0; x < bitmap.width; ++x)
                {
                    const int atlasX = offsetX + static_cast<int>(x);
                    const int atlasY = offsetY + static_cast<int>(y);
                    atlas[static_cast<size_t>(atlasY * _atlasWidth + atlasX)]
                        = bitmap.buffer[y * bitmap.pitch + x];
                }
            }

            Glyph glyph;
            glyph.uvMin = glm::vec2(static_cast<float>(offsetX) / static_cast<float>(_atlasWidth),
                                    static_cast<float>(offsetY) / static_cast<float>(_atlasHeight));
            glyph.uvMax = glm::vec2(static_cast<float>(offsetX + bitmap.width)
                                        / static_cast<float>(_atlasWidth),
                                    static_cast<float>(offsetY + bitmap.rows)
                                        / static_cast<float>(_atlasHeight));
            glyph.size = glm::vec2(bitmap.width, bitmap.rows);
            glyph.bearing = glm::vec2(glyphSlot->bitmap_left, glyphSlot->bitmap_top);
            glyph.advance = static_cast<float>(glyphSlot->advance.x >> 6);
            _glyphs[character] = glyph;

            offsetX += static_cast<int>(bitmap.width) + AtlasPadding;
            rowHeight = std::max(rowHeight, static_cast<int>(bitmap.rows));
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures(1, &_atlasId);
        glBindTexture(GL_TEXTURE_2D, _atlasId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _atlasWidth, _atlasHeight, 0, GL_RED,
                     GL_UNSIGNED_BYTE, atlas.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        FT_Done_Face(face);
        FT_Done_FreeType(library);
    }
} // namespace GFX::Graphics
