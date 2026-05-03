#include "GFX/Graphics/RawGraphics/include/VertexArrayObject.h"

#include <algorithm>

namespace GFX::Graphics
{

    VertexArrayObject::VertexArrayObject() { glGenVertexArrays(1, &_id); }

    VertexArrayObject::~VertexArrayObject() { glDeleteVertexArrays(1, &_id); }

    VertexArrayObject::VertexArrayObject(VertexArrayObject&& other) noexcept
    {
        *this = std::move(other);
    }
    VertexArrayObject& VertexArrayObject::operator=(VertexArrayObject&& other) noexcept
    {
        _id = other._id;
        other._id = 0;
        return *this;
    }

    void VertexArrayObject::addBuffer(const VertexBufferObject& vbo,
                                      const VertexBufferLayout& layout) const
    {
        bind();
        vbo.bind();

        const auto& elements = layout.getElements();
        GLuint offset = 0;

        for (GLuint i = 0; i < elements.size(); i++)
        {
            const auto& e = elements[i];

            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, e.count, e.type, e.normalized, layout.getStride(),
                                  reinterpret_cast<const void*>(static_cast<uintptr_t>(offset)));

            offset += e.count * VertexBufferElement::getSizeOfType(e.type);
        }
    }

    void VertexArrayObject::bind() const { glBindVertexArray(_id); }

    void VertexArrayObject::unbind() { glBindVertexArray(0); }

} // namespace gfx2d