#include "GFX/Graphics/RawGraphics/include/Mesh.h"

namespace GFX::Graphics
{

    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
    {
        _vao.bind();
        _vbo.setData(vertices.data(), vertices.size() * sizeof(Vertex));
        _ebo.setData(indices.data(), indices.size() * sizeof(uint32_t));

        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);

        _vao.addBuffer(_vbo, layout);

        _indexCount = static_cast<uint32_t>(indices.size());
    }
} // namespace gfx2d