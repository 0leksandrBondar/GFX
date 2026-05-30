#pragma once

#include "GFX/Core/Camera/include/Camera.h"
#include "GFX/Graphics/Graphics/include/Text.h"
#include "GFX/Graphics/RawGraphics/include/Shader.h"

#include "ExternalLibs/GLM/glm/vec2.hpp"
#include "ExternalLibs/GLM/glm/vec3.hpp"

#include <vector>

namespace GFX::Graphics
{
    class TextRenderer final : public Core::NonCopyableButMovable
    {
    public:
        explicit TextRenderer(ShaderPtr shader);
        ~TextRenderer();

        TextRenderer(TextRenderer&& other) noexcept;
        TextRenderer& operator=(TextRenderer&& other) noexcept;

        void draw(const Text& text, const Core::Camera& camera);
        void setDepthTestEnabled(bool enabled) { _depthTestEnabled = enabled; }
        [[nodiscard]] bool isDepthTestEnabled() const { return _depthTestEnabled; }

    private:
        struct TextVertex
        {
            glm::vec3 position{ 0.0f };
            glm::vec2 uv{ 0.0f };
        };

        void appendGlyph(std::vector<TextVertex>& vertices, std::vector<unsigned int>& indices,
                         const Font& font, const Glyph& glyph, float penX, float penY,
                         float boldOffset);

    private:
        ShaderPtr _shader{ nullptr };
        GLuint _vao{ 0 };
        GLuint _vbo{ 0 };
        GLuint _ebo{ 0 };
        bool _depthTestEnabled{ false };
    };
} // namespace GFX::Graphics
