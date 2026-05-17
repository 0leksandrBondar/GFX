#pragma once

#include "ElementBufferObject.h"
#include "GFX/Core/BaseTypes/include/Transformable.h"
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

    class Mesh final : public Core::Transformable
    {
    public:
        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

        void bindVertexArrayObject() const { _vao.bind(); }
        void draw() const;

        [[nodiscard]] uint32_t getIndexCount() const { return _indexCount; }
        [[nodiscard]] const glm::mat4& getModelMatrix() const { return getTransformMatrix(); }

    private:
        void updateBounds(const std::vector<Vertex>& vertices);

    private:
        VertexArrayObject _vao;
        VertexBufferObject _vbo;
        ElementBufferObject _ebo;
        uint32_t _indexCount{ 0 };
    };
} // namespace gfx2d
