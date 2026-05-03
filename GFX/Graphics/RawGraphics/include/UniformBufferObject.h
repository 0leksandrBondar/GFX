#pragma once

#include "ExternalLibs/GLAD/include/glad/glad.h"
#include "GFX/Core/BaseTypes/include/NonCopyableButMovable.h"

namespace GFX::Graphics
{
    class UniformBufferObject final : public Core::NonCopyableButMovable
    {
    public:
        UniformBufferObject();
        ~UniformBufferObject();

        void create(int size, GLuint bindingPoint);

        void bind() const;
        void unbind() const;

        void updateData(const void* data, int size, int offset = 0);

        GLuint getID() const { return _id; }

    private:
        GLuint _id = 0;
        GLuint _bindingPoint = 0;
        int _size = 0;
    };
} // namespace gfx2d