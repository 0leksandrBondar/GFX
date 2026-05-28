#include "GFX/Graphics/Graphics/include/Model.h"

#include "GFX/Graphics/RawGraphics/include/VertexBufferLayout.h"

#include <algorithm>
#include <filesystem>

namespace GFX::Graphics
{
    Model::Model(const std::filesystem::path& path)
    {
        setVertices(Core::Loader::loadModel(path));
    }

    Model::Model(const std::vector<Core::Vertex>& vertices)
    {
        setVertices(vertices);
    }

    Model Model::load(const std::filesystem::path& path)
    {
        return Model(path);
    }

    void Model::setVertices(const std::vector<Core::Vertex>& vertices)
    {
        updateBounds(vertices);

        _vbo.setData(vertices.data(), vertices.size() * sizeof(Core::Vertex));

        VertexBufferLayout layout;
        layout.push<float>(3);
        layout.push<float>(2);
        layout.push<float>(3);

        _vao.addBuffer(_vbo, layout);
        _vertexCount = static_cast<GLsizei>(vertices.size());
    }

    void Model::updateBounds(const std::vector<Core::Vertex>& vertices)
    {
        if (vertices.empty())
            return;

        glm::vec3 minPosition(vertices.front().position.x, vertices.front().position.y,
                              vertices.front().position.z);
        glm::vec3 maxPosition = minPosition;

        for (const Core::Vertex& vertex : vertices)
        {
            const glm::vec3 position(vertex.position.x, vertex.position.y, vertex.position.z);
            minPosition.x = std::min(minPosition.x, position.x);
            minPosition.y = std::min(minPosition.y, position.y);
            minPosition.z = std::min(minPosition.z, position.z);
            maxPosition.x = std::max(maxPosition.x, position.x);
            maxPosition.y = std::max(maxPosition.y, position.y);
            maxPosition.z = std::max(maxPosition.z, position.z);
        }

        setLocalBounds(minPosition, maxPosition - minPosition);
    }
} // namespace GFX::Graphics
