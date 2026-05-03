#pragma once

#include "GFX/Graphics/RawGraphics/include/RawTexture.h"

#include <filesystem>

namespace GFX::Graphics
{
    using TexturePtr = std::shared_ptr<class Texture>;

    class Texture final
    {
    public:
        static TexturePtr create(const std::filesystem::path& path);

    public:
        Texture() = default;
        explicit Texture(const std::filesystem::path& path);

    public:
        void use() const { _raw->bind(); }
        void unuse() const { GFX::Graphics::RawTexture::unbind(); }

        [[nodiscard]] int getWidth() const { return _width; }
        [[nodiscard]] int getHeight() const { return _height; }
        //[[nodiscard]] Rect geTextureRect() const { return _rect; }

        void setSmooth(bool smooth);
        //  void setTextureRect(const Rect& rect) { _rect = rect; }

    private:
        void loadTexture(const std::filesystem::path& path);

    private:
        RawTexturePtr _raw{ nullptr };
        // Rect _rect{};
        int channels{ 0 };
        int _width{};
        int _height{};
        bool _isSmooth{ false };
    };
} // namespace GFX::Graphics