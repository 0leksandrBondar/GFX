#include "GFX/Graphics/RawGraphics/include/ElementBufferObject.h"

#include <algorithm>

namespace GFX::Graphics
{
    ElementBufferObject::ElementBufferObject() { glGenBuffers(1, &_id); }

    ElementBufferObject::~ElementBufferObject() { glDeleteBuffers(1, &_id); }

    ElementBufferObject::ElementBufferObject(ElementBufferObject&& other) noexcept
    {
        *this = std::move(other);
    }

    ElementBufferObject& ElementBufferObject::operator=(ElementBufferObject&& other) noexcept
    {
        _id = other._id;
        other._id = 0;
        return *this;
    }

    void ElementBufferObject::setData(const void* vertices, const unsigned int size) const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    void ElementBufferObject::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id); }

    void ElementBufferObject::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

} // namespace gfx2d