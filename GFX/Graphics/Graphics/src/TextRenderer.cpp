#include "GFX/Graphics/Graphics/include/TextRenderer.h"

#include <cstddef>
#include <utility>

namespace GFX::Graphics
{
    namespace
    {
        std::vector<char32_t> decodeUtf8(const std::string& text)
        {
            std::vector<char32_t> result;
            result.reserve(text.size());

            for (size_t i = 0; i < text.size();)
            {
                const auto byte = static_cast<unsigned char>(text[i]);

                if ((byte & 0x80) == 0)
                {
                    result.push_back(byte);
                    ++i;
                }
                else if ((byte & 0xE0) == 0xC0 && i + 1 < text.size())
                {
                    result.push_back(((byte & 0x1F) << 6)
                                     | (static_cast<unsigned char>(text[i + 1]) & 0x3F));
                    i += 2;
                }
                else if ((byte & 0xF0) == 0xE0 && i + 2 < text.size())
                {
                    result.push_back(((byte & 0x0F) << 12)
                                     | ((static_cast<unsigned char>(text[i + 1]) & 0x3F) << 6)
                                     | (static_cast<unsigned char>(text[i + 2]) & 0x3F));
                    i += 3;
                }
                else if ((byte & 0xF8) == 0xF0 && i + 3 < text.size())
                {
                    result.push_back(((byte & 0x07) << 18)
                                     | ((static_cast<unsigned char>(text[i + 1]) & 0x3F) << 12)
                                     | ((static_cast<unsigned char>(text[i + 2]) & 0x3F) << 6)
                                     | (static_cast<unsigned char>(text[i + 3]) & 0x3F));
                    i += 4;
                }
                else
                {
                    ++i;
                }
            }

            return result;
        }
    } // namespace

    TextRenderer::TextRenderer()
    {
        glGenVertexArrays(1, &_vao);
        glGenBuffers(1, &_vbo);
        glGenBuffers(1, &_ebo);

        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TextVertex),
                              reinterpret_cast<const void*>(offsetof(TextVertex, position)));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex),
                              reinterpret_cast<const void*>(offsetof(TextVertex, uv)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBindVertexArray(0);
    }

    TextRenderer::~TextRenderer()
    {
        glDeleteBuffers(1, &_ebo);
        glDeleteBuffers(1, &_vbo);
        glDeleteVertexArrays(1, &_vao);
    }

    TextRenderer::TextRenderer(TextRenderer&& other) noexcept
    {
        *this = std::move(other);
    }

    TextRenderer& TextRenderer::operator=(TextRenderer&& other) noexcept
    {
        if (this == &other)
            return *this;

        glDeleteBuffers(1, &_ebo);
        glDeleteBuffers(1, &_vbo);
        glDeleteVertexArrays(1, &_vao);

        _defaultShader = std::move(other._defaultShader);
        _vao = other._vao;
        _vbo = other._vbo;
        _ebo = other._ebo;

        other._vao = 0;
        other._vbo = 0;
        other._ebo = 0;
        return *this;
    }

    void TextRenderer::draw(const Text& text, const Core::Camera& camera)
    {
        const FontPtr& font = text.getFont();
        const ShaderPtr& shader = text.getShader() ? text.getShader() : _defaultShader;

        if (!font || !shader || text.getString().empty())
            return;

        std::vector<TextVertex> vertices;
        std::vector<unsigned int> indices;
        const std::vector<char32_t> characters = decodeUtf8(text.getString());
        vertices.reserve(characters.size() * (text.isBold() ? 8 : 4));
        indices.reserve(characters.size() * (text.isBold() ? 12 : 6));

        float penX = 0.0f;
        float penY = 0.0f;
        const float boldOffset = text.isBold() ? static_cast<float>(font->getPixelSize()) * 0.035f
                                               : 0.0f;

        for (const char32_t character : characters)
        {
            if (character == '\n')
            {
                penX = 0.0f;
                penY += font->getLineHeight();
                continue;
            }

            const Glyph* glyph = font->getGlyph(character);
            if (!glyph)
                continue;

            appendGlyph(vertices, indices, *font, *glyph, penX, penY, 0.0f);
            if (text.isBold())
                appendGlyph(vertices, indices, *font, *glyph, penX, penY, boldOffset);

            penX += glyph->advance;
        }

        if (indices.empty())
            return;

        shader->use();
        shader->setMatrix4("uModel", text.getTransformMatrix());
        shader->setMatrix4("uView", camera.getViewMatrix());
        shader->setMatrix4("uProjection", camera.getProjectionMatrix());
        shader->setVector4("uColor", text.getColor().toVec4());
        shader->setInt("uFontAtlas", 0);

        font->bind(0);

        const GLboolean wasDepthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
        if (!_depthTestEnabled)
            glDisable(GL_DEPTH_TEST);

        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(TextVertex)),
                     vertices.data(), GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     static_cast<GLsizeiptr>(indices.size() * sizeof(unsigned int)), indices.data(),
                     GL_DYNAMIC_DRAW);

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT,
                       nullptr);

        Font::unbind();
        glBindVertexArray(0);

        if (!_depthTestEnabled && wasDepthTestEnabled)
            glEnable(GL_DEPTH_TEST);
    }

    void TextRenderer::appendGlyph(std::vector<TextVertex>& vertices,
                                   std::vector<unsigned int>& indices, const Font& font,
                                   const Glyph& glyph, const float penX, const float penY,
                                   const float boldOffset)
    {
        const float x = penX + glyph.bearing.x + boldOffset;
        const float y = penY + (font.getAscender() - glyph.bearing.y);
        constexpr float z = 0.0f;
        const float w = glyph.size.x;
        const float h = glyph.size.y;

        const unsigned int start = static_cast<unsigned int>(vertices.size());
        vertices.push_back({ glm::vec3(x, y, z), glm::vec2(glyph.uvMin.x, glyph.uvMin.y) });
        vertices.push_back({ glm::vec3(x, y + h, z), glm::vec2(glyph.uvMin.x, glyph.uvMax.y) });
        vertices.push_back({ glm::vec3(x + w, y + h, z), glm::vec2(glyph.uvMax.x, glyph.uvMax.y) });
        vertices.push_back({ glm::vec3(x + w, y, z), glm::vec2(glyph.uvMax.x, glyph.uvMin.y) });

        indices.push_back(start + 0);
        indices.push_back(start + 1);
        indices.push_back(start + 2);
        indices.push_back(start + 0);
        indices.push_back(start + 2);
        indices.push_back(start + 3);
    }
} // namespace GFX::Graphics
