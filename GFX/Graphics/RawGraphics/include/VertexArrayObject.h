#pragma once

#include "VertexBufferLayout.h"
#include "VertexBufferObject.h"
#include "ExternalLibs/GLAD/include/glad/glad.h"

namespace GFX::Graphics
{
    class VertexArrayObject final : public Core::NonCopyableButMovable
    {
    public:
        VertexArrayObject();
        ~VertexArrayObject();

        VertexArrayObject(VertexArrayObject&& other) noexcept;
        VertexArrayObject& operator=(VertexArrayObject&& other) noexcept;

        void addBuffer(const VertexBufferObject& vbo, const VertexBufferLayout& layout) const;

        void bind() const;
        static void unbind();

    private:
        GLuint _id{ 0 };
    };

} // namespace gfx2d