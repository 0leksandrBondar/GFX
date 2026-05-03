#pragma once

#include "ElementBufferObject.h"
#include "VertexArrayObject.h"
#include "glm/vec2.hpp"
#include <vector>

namespace GFX::Graphics
{
    struct Vertex
    {
        glm::vec2 Position;
        glm::vec2 ColorPosition;
    };

    class Mesh final
    {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

        void bindVertexArrayObject() const { _vao.bind(); }
        [[nodiscard]] uint32_t getIndexCount() const { return _indexCount; }

    private:
        VertexArrayObject _vao;
        VertexBufferObject _vbo;
        ElementBufferObject _ebo;
        uint32_t _indexCount;
    };
} // namespace gfx2d
