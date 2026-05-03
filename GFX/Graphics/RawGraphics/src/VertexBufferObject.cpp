#include "GFX/Graphics/RawGraphics/include/VertexBufferObject.h"

#include <algorithm>

namespace GFX::Graphics
{
    VertexBufferObject::VertexBufferObject() { glGenBuffers(1, &_id); }

    VertexBufferObject::~VertexBufferObject() { glDeleteBuffers(1, &_id); }

    VertexBufferObject::VertexBufferObject(VertexBufferObject&& other) noexcept
    {
        *this = std::move(other);
    }

    VertexBufferObject& VertexBufferObject::operator=(VertexBufferObject&& other) noexcept
    {
        _id = other._id;
        other._id = 0;
        return *this;
    }

    void VertexBufferObject::setData(const void* vertices, const unsigned int size) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, _id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    void VertexBufferObject::bind() const { glBindBuffer(GL_ARRAY_BUFFER, _id); }

    void VertexBufferObject::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

} // namespace gfx2d