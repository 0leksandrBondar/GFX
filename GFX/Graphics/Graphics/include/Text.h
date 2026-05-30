#pragma once

#include "ExternalLibs/GLM/glm/vec4.hpp"
#include "GFX/Core/BaseTypes/include/Transformable.h"
#include "GFX/Graphics/Graphics/include/Font.h"

#include <string>
#include <utility>

namespace GFX::Graphics
{
    class Text final : public Core::Transformable
    {
    public:
        Text() = default;
        Text(FontPtr font, std::string string = "");

        void setFont(FontPtr font) { _font = std::move(font); }
        void setString(std::string string) { _string = std::move(string); }
        void setColor(const glm::vec4& color) { _color = color; }
        void setBold(bool bold) { _bold = bold; }

        [[nodiscard]] const FontPtr& getFont() const { return _font; }
        [[nodiscard]] const std::string& getString() const { return _string; }
        [[nodiscard]] const glm::vec4& getColor() const { return _color; }
        [[nodiscard]] bool isBold() const { return _bold; }

    private:
        FontPtr _font{ nullptr };
        std::string _string;
        glm::vec4 _color{ 1.0f };
        bool _bold{ false };
    };
} // namespace GFX::Graphics
