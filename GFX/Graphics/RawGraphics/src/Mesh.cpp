#include "GFX/Graphics/RawGraphics/include/Mesh.h"

#include <algorithm>

namespace GFX::Graphics
{

    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
    {
        updateBounds(vertices);

        _vao.bind();
        _vbo.setData(vertices.data(), vertices.size() * sizeof(Vertex));
        _ebo.setData(indices.data(), indices.size() * sizeof(uint32_t));

        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);

        _vao.addBuffer(_vbo, layout);

        _indexCount = static_cast<uint32_t>(indices.size());
    }

    void Mesh::draw() const
    {
        _vao.bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(_indexCount), GL_UNSIGNED_INT, nullptr);
    }

    void Mesh::updateBounds(const std::vector<Vertex>& vertices)
    {
        if (vertices.empty())
            return;

        glm::vec2 minPosition = vertices.front().Position;
        glm::vec2 maxPosition = vertices.front().Position;

        for (const Vertex& vertex : vertices)
        {
            minPosition.x = std::min(minPosition.x, vertex.Position.x);
            minPosition.y = std::min(minPosition.y, vertex.Position.y);
            maxPosition.x = std::max(maxPosition.x, vertex.Position.x);
            maxPosition.y = std::max(maxPosition.y, vertex.Position.y);
        }

        const glm::vec2 size = maxPosition - minPosition;
        setLocalBounds(glm::vec3(minPosition.x, minPosition.y, 0.0f),
                       glm::vec3(size.x, size.y, 0.0f));
    }
} // namespace gfx2d
