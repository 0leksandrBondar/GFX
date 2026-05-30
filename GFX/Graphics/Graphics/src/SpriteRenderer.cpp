#include "GFX/Graphics/Graphics/include/SpriteRenderer.h"

#include <array>
#include <cstddef>
#include <utility>

namespace GFX::Graphics
{
    SpriteRenderer::SpriteRenderer()
    {
        glGenVertexArrays(1, &_vao);
        glGenBuffers(1, &_vbo);
        glGenBuffers(1, &_ebo);

        constexpr std::array<unsigned int, 6> indices{ 0, 1, 2, 0, 2, 3 };

        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(SpriteVertex), nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex),
                              reinterpret_cast<const void*>(offsetof(SpriteVertex, position)));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex),
                              reinterpret_cast<const void*>(offsetof(SpriteVertex, uv)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(),
                     GL_STATIC_DRAW);
        glBindVertexArray(0);
    }

    SpriteRenderer::~SpriteRenderer()
    {
        glDeleteBuffers(1, &_ebo);
        glDeleteBuffers(1, &_vbo);
        glDeleteVertexArrays(1, &_vao);
    }

    SpriteRenderer::SpriteRenderer(SpriteRenderer&& other) noexcept
    {
        *this = std::move(other);
    }

    SpriteRenderer& SpriteRenderer::operator=(SpriteRenderer&& other) noexcept
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
        _depthTestEnabled = other._depthTestEnabled;

        other._vao = 0;
        other._vbo = 0;
        other._ebo = 0;
        return *this;
    }

    void SpriteRenderer::draw(const Sprite& sprite, const Core::Camera& camera)
    {
        const TexturePtr& texture = sprite.getTexture();
        const ShaderPtr& shader = sprite.getShader() ? sprite.getShader() : _defaultShader;

        if (!texture || !shader)
            return;

        const TextureRect& rect = sprite.getTextureRect();
        if (rect.width == 0.0f || rect.height == 0.0f)
            return;

        const float textureWidth = static_cast<float>(texture->getWidth());
        const float textureHeight = static_cast<float>(texture->getHeight());

        const float u0 = rect.left / textureWidth;
        const float v0 = rect.top / textureHeight;
        const float u1 = (rect.left + rect.width) / textureWidth;
        const float v1 = (rect.top + rect.height) / textureHeight;

        const std::array<SpriteVertex, 4> vertices{
            SpriteVertex{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(u0, v0) },
            SpriteVertex{ glm::vec3(0.0f, rect.height, 0.0f), glm::vec2(u0, v1) },
            SpriteVertex{ glm::vec3(rect.width, rect.height, 0.0f), glm::vec2(u1, v1) },
            SpriteVertex{ glm::vec3(rect.width, 0.0f, 0.0f), glm::vec2(u1, v0) },
        };

        shader->use();
        shader->setMatrix4("uModel", sprite.getTransformMatrix());
        shader->setMatrix4("uView", camera.getViewMatrix());
        shader->setMatrix4("uProjection", camera.getProjectionMatrix());
        shader->setVector4("uColor", sprite.getColor().toVec4());
        shader->setInt("uTexture", 0);

        glActiveTexture(GL_TEXTURE0);
        texture->use();

        const GLboolean wasDepthTestEnabled = glIsEnabled(GL_DEPTH_TEST);
        if (!_depthTestEnabled)
            glDisable(GL_DEPTH_TEST);

        glBindVertexArray(_vao);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, static_cast<GLsizeiptr>(sizeof(SpriteVertex) * vertices.size()),
                        vertices.data());

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        texture->unuse();
        glBindVertexArray(0);

        if (!_depthTestEnabled && wasDepthTestEnabled)
            glEnable(GL_DEPTH_TEST);
    }
} // namespace GFX::Graphics
