#pragma once

#include "GFX/Core/BaseTypes/include/Transformable.h"
#include "GFX/Core/Loader/include/Loader.h"
#include "GFX/Graphics/RawGraphics/include/VertexArrayObject.h"
#include "GFX/Graphics/RawGraphics/include/VertexBufferObject.h"

#include <filesystem>
#include <vector>

namespace GFX::Graphics
{
    class Model final : public Core::Transformable
    {
    public:
        explicit Model(const std::filesystem::path& path);
        explicit Model(const std::vector<Core::Vertex>& vertices);

        static Model load(const std::filesystem::path& path);

        void bind() const { _vao.bind(); }

        [[nodiscard]] const glm::mat4& getModelMatrix() const { return getTransformMatrix(); }
        [[nodiscard]] GLsizei getVertexCount() const { return _vertexCount; }

    private:
        void setVertices(const std::vector<Core::Vertex>& vertices);
        void updateBounds(const std::vector<Core::Vertex>& vertices);

    private:
        VertexArrayObject _vao;
        VertexBufferObject _vbo;
        GLsizei _vertexCount{ 0 };
    };
} // namespace GFX::Graphics
