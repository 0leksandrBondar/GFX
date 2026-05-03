#include "GFX/Core/Loader/include/Loader.h"

#include "spdlog/spdlog.h"

#include <fstream>
#include <sstream>

namespace GFX::Core
{
    std::vector<Vertex> Loader::loadOBJ(const std::filesystem::path& path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            spdlog::warn("LoadOBJ: Could not open file {}", path.string());
            return {};
        }

        std::vector<Vec3> positions;
        std::vector<Vec2> uvs;
        std::vector<Vec3> normals;

        std::vector<Vertex> vertices;

        std::string line;

        while (std::getline(file, line))
        {
            std::istringstream ss(line);
            std::string prefix;
            ss >> prefix;

            if (prefix == "v")
            {
                Vec3 v{};
                ss >> v.x >> v.y >> v.z;
                positions.push_back(v);
            }
            else if (prefix == "vt")
            {
                Vec2 vt{};
                ss >> vt.u >> vt.v;
                uvs.push_back(vt);
            }
            else if (prefix == "vn")
            {
                Vec3 vn{};
                ss >> vn.x >> vn.y >> vn.z;
                normals.push_back(vn);
            }
            else if (prefix == "f")
            {
                std::string v1, v2, v3, v4;
                ss >> v1 >> v2 >> v3 >> v4;

                std::vector<std::string> face = { v1, v2, v3 };
                if (!v4.empty())
                    face.push_back(v4);

                // триангуляция
                for (int i = 1; i < face.size() - 1; i++)
                {
                    std::string tri[3] = { face[0], face[i], face[i + 1] };

                    for (const auto& k : tri)
                    {
                        std::istringstream vs(k);
                        std::string p, t, n;

                        std::getline(vs, p, '/');
                        std::getline(vs, t, '/');
                        std::getline(vs, n, '/');

                        int pi = std::stoi(p) - 1;
                        int ti = std::stoi(t) - 1;
                        int ni = std::stoi(n) - 1;

                        Vertex vert{};
                        vert.position = positions[pi];
                        vert.uv = uvs[ti];
                        vert.normal = normals[ni];

                        vertices.push_back(vert);
                    }
                }
            }
        }

        return vertices;
    }

} // namespace GFX::Core
