#pragma once

#include "ExternalLibs/GLM/glm/vec4.hpp"
#include "GFX/Core/BaseTypes/include/Transformable.h"
#include "GFX/Graphics/Graphics/include/Color.h"
#include "GFX/Graphics/Graphics/include/Font.h"
#include "GFX/Graphics/RawGraphics/include/Shader.h"

#include <string>
#include <utility>

namespace GFX::Graphics
{
    class Text final : public Core::Transformable
    {
    public:
        Text() = default;
        Text(FontPtr font, std::string string = "");
        Text(FontPtr font, ShaderPtr shader, std::string string = "");

        void setFont(FontPtr font) { _font = std::move(font); }
        void setShader(ShaderPtr shader) { _shader = std::move(shader); }
        void setString(std::string string) { _string = std::move(string); }
        void setColor(const Color& color) { _color = color; }
        void setColor(const glm::vec4& color) { _color = { color.r, color.g, color.b, color.a }; }
        void setOpacity(float opacity) { _color.a = opacity; }
        void setBold(bool bold) { _bold = bold; }

        [[nodiscard]] const FontPtr& getFont() const { return _font; }
        [[nodiscard]] const ShaderPtr& getShader() const { return _shader; }
        [[nodiscard]] const std::string& getString() const { return _string; }
        [[nodiscard]] const Color& getColor() const { return _color; }
        [[nodiscard]] float getOpacity() const { return _color.a; }
        [[nodiscard]] bool isBold() const { return _bold; }

    private:
        FontPtr _font{ nullptr };
        ShaderPtr _shader{ nullptr };
        std::string _string;
        Color _color{ Colors::White };
        bool _bold{ false };
    };
} // namespace GFX::Graphics
