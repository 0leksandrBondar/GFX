#pragma once

#include "ExternalLibs/GLM/glm/vec2.hpp"
#include "ExternalLibs/GLM/glm/vec3.hpp"
#include "GFX/Core/Camera/include/Camera.h"
#include "GFX/Graphics/Graphics/include/Sprite.h"

#include <utility>
#include <vector>

namespace GFX::Graphics
{
    class SpriteRenderer final : public Core::NonCopyableButMovable
    {
    public:
        SpriteRenderer();
        ~SpriteRenderer();

        SpriteRenderer(SpriteRenderer&& other) noexcept;
        SpriteRenderer& operator=(SpriteRenderer&& other) noexcept;

        void draw(const Sprite& sprite, const Core::Camera& camera);
        void setDefaultShader(ShaderPtr shader) { _defaultShader = std::move(shader); }
        [[nodiscard]] const ShaderPtr& getDefaultShader() const { return _defaultShader; }
        void setDepthTestEnabled(bool enabled) { _depthTestEnabled = enabled; }
        [[nodiscard]] bool isDepthTestEnabled() const { return _depthTestEnabled; }

    private:
        struct SpriteVertex
        {
            glm::vec3 position{ 0.0f };
            glm::vec2 uv{ 0.0f };
        };

    private:
        ShaderPtr _defaultShader{ nullptr };
        GLuint _vao{ 0 };
        GLuint _vbo{ 0 };
        GLuint _ebo{ 0 };
        bool _depthTestEnabled{ false };
    };
} // namespace GFX::Graphics
