#pragma once

#include "ExternalLibs/GLAD/include/glad/glad.h"
#include "ExternalLibs/GLM/glm/vec2.hpp"
#include "GFX/Core/BaseTypes/include/NonCopyableButMovable.h"

#include <filesystem>
#include <memory>
#include <unordered_map>

namespace GFX::Graphics
{
    using FontPtr = std::shared_ptr<class Font>;

    struct Glyph
    {
        glm::vec2 uvMin{ 0.0f };
        glm::vec2 uvMax{ 0.0f };
        glm::vec2 size{ 0.0f };
        glm::vec2 bearing{ 0.0f };
        float advance{ 0.0f };
    };

    class Font final : public Core::NonCopyableButMovable
    {
    public:
        static FontPtr create(const std::filesystem::path& path, unsigned int pixelSize);

    public:
        Font(const std::filesystem::path& path, unsigned int pixelSize);
        ~Font();

        Font(Font&& other) noexcept;
        Font& operator=(Font&& other) noexcept;

        void bind(unsigned int slot = 0) const;
        static void unbind();

        [[nodiscard]] const Glyph* getGlyph(char32_t character) const;
        [[nodiscard]] unsigned int getPixelSize() const { return _pixelSize; }
        [[nodiscard]] float getLineHeight() const { return _lineHeight; }
        [[nodiscard]] float getAscender() const { return _ascender; }
        [[nodiscard]] GLuint getAtlasId() const { return _atlasId; }

    private:
        void load(const std::filesystem::path& path);

    private:
        std::unordered_map<char32_t, Glyph> _glyphs;
        GLuint _atlasId{ 0 };
        unsigned int _pixelSize{ 0 };
        int _atlasWidth{ 0 };
        int _atlasHeight{ 0 };
        float _lineHeight{ 0.0f };
        float _ascender{ 0.0f };
    };
} // namespace GFX::Graphics
