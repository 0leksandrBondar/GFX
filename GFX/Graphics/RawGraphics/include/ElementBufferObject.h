#pragma once

#include "GFX/Core/BaseTypes/include/NonCopyableButMovable.h"
#include "glad/glad.h"

namespace GFX::Graphics
{
    class ElementBufferObject final : public Core::NonCopyableButMovable
    {
    public:
        ElementBufferObject();
        ~ElementBufferObject();

        ElementBufferObject(ElementBufferObject&& other) noexcept;
        ElementBufferObject& operator=(ElementBufferObject&& other) noexcept;

        void setData(const void* vertices, unsigned int size) const;

        void bind() const;
        void unbind() const;

    private:
        GLuint _id{ 0 };
    };
} // namespace GFX::Graphics