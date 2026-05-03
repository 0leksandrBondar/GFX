#pragma once

#include "ExternalLibs/GLAD/include/glad/glad.h"
#include "ExternalLibs/GLM/glm/mat4x4.hpp"
#include "ExternalLibs/GLM/glm/vec4.hpp"
#include "GFX/Core/BaseTypes/include/NonCopyableButMovable.h"

#include <filesystem>

namespace GFX::Graphics
{

    using ShaderPtr = std::shared_ptr<class Shader>;

    class Shader final : public Core::NonCopyableButMovable
    {
    public:
        static ShaderPtr create(const std::string& vertexShader, const std::string& fragmentShader);

    public:
        Shader(const std::filesystem::path& vertexShaderPath,
               const std::filesystem::path& fragmentShaderPath);
        ~Shader();

    public:
        void use() const;

        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setBool(const std::string& name, bool value) const;
        void setVector4(const std::string& name, const glm::vec4& value) const;
        void setVector3(const std::string& name, const glm::vec3& value) const;
        void setMatrix4(const std::string& name, const glm::mat4& matrix) const;

    private:
        int getUniformLocation(const std::string& name) const;

        void validateProgramLinking(GLuint shaderID) const;
        void validateShaderCompilation(GLuint shaderID) const;
        void createProgram(GLuint vertexShader, GLuint fragmentShader);
        GLuint createShader(const std::string& source, GLenum shaderType);
        std::string getShaderProgramSourceCode(const std::filesystem::path& shaderProgramPath);

    private:
        GLuint _id{ 0 };
        mutable std::unordered_map<std::string, int> _uniformCache;
    };
} // namespace GFX::Graphics
