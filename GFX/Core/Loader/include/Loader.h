#pragma once

#include <filesystem>
#include <vector>

namespace GFX::Core
{
    struct Vec3
    {
        float x, y, z;
    };
    struct Vec2
    {
        float u, v;
    };

    struct Vertex
    {
        Vec3 position;
        Vec2 uv;
        Vec3 normal;
    };

    class Loader
    {
    public:
        Loader() = default;
        ~Loader() = default;

    public:
        static std::vector<Vertex> loadModel(const std::filesystem::path& path);
        static std::vector<Vertex> loadOBJ(const std::filesystem::path& path);
    };
} // namespace GFX::Core
