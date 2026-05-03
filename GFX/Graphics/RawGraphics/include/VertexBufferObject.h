#pragma once
#include "GFX/Core/BaseTypes/include/NonCopyableButMovable.h"

#include "ExternalLibs/GLAD/include/glad/glad.h"

namespace GFX::Graphics
{
    class VertexBufferObject final : public Core::NonCopyableButMovable
    {
    public:
        VertexBufferObject();
        ~VertexBufferObject();
        VertexBufferObject(VertexBufferObject&& other) noexcept;
        VertexBufferObject& operator=(VertexBufferObject&& other) noexcept;

        void setData(const void* vertices, unsigned int size) const;

        void bind() const;
        void unbind();

    private:
        GLuint _id{ 0 };
    };
} // namespace gfx2d