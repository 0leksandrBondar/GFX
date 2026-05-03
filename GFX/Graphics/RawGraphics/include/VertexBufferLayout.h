#pragma once

#include "ExternalLibs/GLAD/include/glad/glad.h"

#include <vector>

namespace GFX::Graphics
{

    struct VertexBufferElement
    {
        GLenum type;
        GLuint count;
        GLboolean normalized;

        static GLuint getSizeOfType(const GLenum type)
        {
            switch (type)
            {
            case GL_FLOAT:
                return 4;
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
            default:;
            }
            return 0;
        }
    };

    class VertexBufferLayout final
    {
    public:
        template <typename T>
        void push(GLuint count);

        [[nodiscard]] const std::vector<VertexBufferElement>& getElements() const
        {
            return _elements;
        }
        [[nodiscard]] GLuint getStride() const { return _stride; }

    private:
        std::vector<VertexBufferElement> _elements;
        GLuint _stride{ 0 };
    };

    template <>
    inline void VertexBufferLayout::push<float>(const GLuint count)
    {
        _elements.push_back({ GL_FLOAT, count, GL_FALSE });
        _stride += count * sizeof(float);
    }
} // namespace gfx2d