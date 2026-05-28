#pragma once

#include "ExternalLibs/GLM/glm/mat4x4.hpp"
#include "ExternalLibs/GLM/glm/vec3.hpp"
#include "ExternalLibs/GLM/glm/vec4.hpp"
#include "GFX/Graphics/Graphics/include/Texture.h"
#include "GFX/Graphics/RawGraphics/include/Shader.h"

#include <string>
#include <vector>

namespace GFX::Graphics
{
    class Material final
    {
    public:
        Material() = default;
        explicit Material(ShaderPtr shader);

        void setShader(ShaderPtr shader) { _shader = std::move(shader); }
        [[nodiscard]] const ShaderPtr& getShader() const { return _shader; }

        void setTexture(const std::string& uniformName, TexturePtr texture, int slot = 0);
        void setInt(const std::string& name, int value);
        void setFloat(const std::string& name, float value);
        void setBool(const std::string& name, bool value);
        void setVector3(const std::string& name, const glm::vec3& value);
        void setVector4(const std::string& name, const glm::vec4& value);
        void setMatrix4(const std::string& name, const glm::mat4& value);

        void apply() const;
        void unuseTextures() const;

    private:
        struct TextureUniform
        {
            std::string name;
            TexturePtr texture;
            int slot{ 0 };
        };

        struct IntUniform
        {
            std::string name;
            int value{ 0 };
        };

        struct FloatUniform
        {
            std::string name;
            float value{ 0.0f };
        };

        struct BoolUniform
        {
            std::string name;
            bool value{ false };
        };

        struct Vector3Uniform
        {
            std::string name;
            glm::vec3 value{ 0.0f };
        };

        struct Vector4Uniform
        {
            std::string name;
            glm::vec4 value{ 0.0f };
        };

        struct Matrix4Uniform
        {
            std::string name;
            glm::mat4 value{ 1.0f };
        };

    private:
        ShaderPtr _shader{ nullptr };
        std::vector<TextureUniform> _textures;
        std::vector<IntUniform> _ints;
        std::vector<FloatUniform> _floats;
        std::vector<BoolUniform> _bools;
        std::vector<Vector3Uniform> _vector3s;
        std::vector<Vector4Uniform> _vector4s;
        std::vector<Matrix4Uniform> _matrix4s;
    };
} // namespace GFX::Graphics
