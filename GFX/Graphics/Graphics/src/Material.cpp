#include "GFX/Graphics/Graphics/include/Material.h"

#include "ExternalLibs/GLAD/include/glad/glad.h"

#include <algorithm>
#include <utility>

namespace GFX::Graphics
{
    namespace
    {
        template <typename Uniform, typename Value>
        void setUniform(std::vector<Uniform>& uniforms, const std::string& name, const Value& value)
        {
            auto it = std::find_if(uniforms.begin(), uniforms.end(),
                                   [&](const Uniform& uniform) { return uniform.name == name; });

            if (it != uniforms.end())
            {
                it->value = value;
                return;
            }

            uniforms.push_back({ name, value });
        }
    } // namespace

    Material::Material(ShaderPtr shader) : _shader(std::move(shader)) {}

    void Material::setTexture(const std::string& uniformName, TexturePtr texture, const int slot)
    {
        auto it = std::find_if(_textures.begin(), _textures.end(),
                               [&](const TextureUniform& uniform)
                               { return uniform.name == uniformName; });

        if (it != _textures.end())
        {
            it->texture = std::move(texture);
            it->slot = slot;
            return;
        }

        _textures.push_back({ uniformName, std::move(texture), slot });
    }

    void Material::setInt(const std::string& name, const int value)
    {
        setUniform(_ints, name, value);
    }

    void Material::setFloat(const std::string& name, const float value)
    {
        setUniform(_floats, name, value);
    }

    void Material::setBool(const std::string& name, const bool value)
    {
        setUniform(_bools, name, value);
    }

    void Material::setVector3(const std::string& name, const glm::vec3& value)
    {
        setUniform(_vector3s, name, value);
    }

    void Material::setVector4(const std::string& name, const glm::vec4& value)
    {
        setUniform(_vector4s, name, value);
    }

    void Material::setMatrix4(const std::string& name, const glm::mat4& value)
    {
        setUniform(_matrix4s, name, value);
    }

    void Material::apply() const
    {
        if (!_shader)
            return;

        _shader->use();

        for (const TextureUniform& textureUniform : _textures)
        {
            if (!textureUniform.texture)
                continue;

            glActiveTexture(GL_TEXTURE0 + textureUniform.slot);
            textureUniform.texture->use();
            _shader->setInt(textureUniform.name, textureUniform.slot);
        }

        for (const IntUniform& uniform : _ints)
            _shader->setInt(uniform.name, uniform.value);
        for (const FloatUniform& uniform : _floats)
            _shader->setFloat(uniform.name, uniform.value);
        for (const BoolUniform& uniform : _bools)
            _shader->setBool(uniform.name, uniform.value);
        for (const Vector3Uniform& uniform : _vector3s)
            _shader->setVector3(uniform.name, uniform.value);
        for (const Vector4Uniform& uniform : _vector4s)
            _shader->setVector4(uniform.name, uniform.value);
        for (const Matrix4Uniform& uniform : _matrix4s)
            _shader->setMatrix4(uniform.name, uniform.value);
    }

    void Material::unuseTextures() const
    {
        for (const TextureUniform& textureUniform : _textures)
        {
            glActiveTexture(GL_TEXTURE0 + textureUniform.slot);
            RawTexture::unbind();
        }

        glActiveTexture(GL_TEXTURE0);
    }
} // namespace GFX::Graphics
