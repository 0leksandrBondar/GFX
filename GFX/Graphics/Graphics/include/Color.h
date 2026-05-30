#pragma once

#include "ExternalLibs/GLM/glm/vec4.hpp"

namespace GFX::Graphics
{
    struct Color
    {
        float r{ 1.0f };
        float g{ 1.0f };
        float b{ 1.0f };
        float a{ 1.0f };

        [[nodiscard]] glm::vec4 toVec4() const { return glm::vec4(r, g, b, a); }

        static constexpr Color fromBytes(unsigned char red, unsigned char green,
                                         unsigned char blue, unsigned char alpha = 255)
        {
            return { static_cast<float>(red) / 255.0f, static_cast<float>(green) / 255.0f,
                     static_cast<float>(blue) / 255.0f, static_cast<float>(alpha) / 255.0f };
        }
    };

    namespace Colors
    {
        inline constexpr Color Transparent{ 1.0f, 1.0f, 1.0f, 0.0f };
        inline constexpr Color White{ 1.0f, 1.0f, 1.0f, 1.0f };
        inline constexpr Color Black{ 0.0f, 0.0f, 0.0f, 1.0f };
        inline constexpr Color Red{ 1.0f, 0.0f, 0.0f, 1.0f };
        inline constexpr Color Green{ 0.0f, 1.0f, 0.0f, 1.0f };
        inline constexpr Color Blue{ 0.0f, 0.0f, 1.0f, 1.0f };
        inline constexpr Color Yellow{ 1.0f, 1.0f, 0.0f, 1.0f };
        inline constexpr Color Cyan{ 0.0f, 1.0f, 1.0f, 1.0f };
        inline constexpr Color Magenta{ 1.0f, 0.0f, 1.0f, 1.0f };
        inline constexpr Color Gray{ 0.5f, 0.5f, 0.5f, 1.0f };
        inline constexpr Color Orange{ 1.0f, 0.5f, 0.0f, 1.0f };
    } // namespace Colors
} // namespace GFX::Graphics
