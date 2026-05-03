#include "GFX/Graphics/RawGraphics/include/UniformBufferObject.h"

#include <spdlog/spdlog.h>

namespace GFX::Graphics
{
    UniformBufferObject::UniformBufferObject() = default;

    UniformBufferObject::~UniformBufferObject()
    {
        if (_id != 0)
        {
            glDeleteBuffers(1, &_id);
        }
    }

    void UniformBufferObject::create(int size, GLuint bindingPoint)
    {
        _size = size;
        _bindingPoint = bindingPoint;

        glGenBuffers(1, &_id);
        glBindBuffer(GL_UNIFORM_BUFFER, _id);
        glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_STATIC_DRAW);

        glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, _id);

        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void UniformBufferObject::bind() const { glBindBuffer(GL_UNIFORM_BUFFER, _id); }

    void UniformBufferObject::unbind() const { glBindBuffer(GL_UNIFORM_BUFFER, 0); }

    void UniformBufferObject::updateData(const void* data, int size, int offset)
    {
        if (offset + size > _size)
        {
            spdlog::error("UBO update out of bounds");
            return;
        }

        glBindBuffer(GL_UNIFORM_BUFFER, _id);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
} // namespace gfx2d