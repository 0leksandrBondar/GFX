#include "GFX/Core/Loader/include/Loader.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "spdlog/spdlog.h"

namespace GFX::Core
{
    namespace
    {
        Vec3 toVec3(const aiVector3D& value)
        {
            return { value.x, value.y, value.z };
        }

        Vec2 toVec2(const aiVector3D& value)
        {
            return { value.x, value.y };
        }
    } // namespace

    std::vector<Vertex> Loader::loadModel(const std::filesystem::path& path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(
            path.string(),
            aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace
                | aiProcess_JoinIdenticalVertices | aiProcess_ImproveCacheLocality
                | aiProcess_OptimizeMeshes);

        if (!scene || !scene->mRootNode || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE))
        {
            spdlog::warn("LoadModel: Could not load file '{}': {}", path.string(),
                         importer.GetErrorString());
            return {};
        }

        std::vector<Vertex> vertices;

        for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
        {
            const aiMesh* mesh = scene->mMeshes[meshIndex];
            if (!mesh)
                continue;

            vertices.reserve(vertices.size() + mesh->mNumFaces * 3);

            for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
            {
                const aiFace& face = mesh->mFaces[faceIndex];
                if (face.mNumIndices != 3)
                {
                    spdlog::warn("LoadModel: Skipping non-triangle face in '{}'", path.string());
                    continue;
                }

                for (unsigned int indexIndex = 0; indexIndex < face.mNumIndices; ++indexIndex)
                {
                    const unsigned int vertexIndex = face.mIndices[indexIndex];

                    Vertex vertex{};
                    vertex.position = toVec3(mesh->mVertices[vertexIndex]);

                    if (mesh->HasTextureCoords(0))
                        vertex.uv = toVec2(mesh->mTextureCoords[0][vertexIndex]);

                    if (mesh->HasNormals())
                        vertex.normal = toVec3(mesh->mNormals[vertexIndex]);

                    vertices.push_back(vertex);
                }
            }
        }

        return vertices;
    }

    std::vector<Vertex> Loader::loadOBJ(const std::filesystem::path& path)
    {
        return loadModel(path);
    }
} // namespace GFX::Core
