#include "ExternalLibs/GLM/glm/ext/matrix_clip_space.hpp"
#include "ExternalLibs/GLM/glm/ext/matrix_transform.hpp"
#include "GFX/Core/Loader/include/Loader.h"
#include "GFX/Core/Window/include/Window.h"
#include "GFX/Graphics/RawGraphics/include/Shader.h"

#include "GFX/Graphics/RawGraphics/include/VertexArrayObject.h"
#include "GFX/Graphics/RawGraphics/include/VertexBufferLayout.h"
#include "GFX/Graphics/RawGraphics/include/VertexBufferObject.h"

#include "ExternalLibs/GLM/glm//gtc/matrix_transform.hpp"
#include "ExternalLibs/GLM/glm/glm.hpp"
#include <memory>

int main()
{
    auto window = std::make_shared<GFX::Core::Window>(1100, 900, "Example");

    GFX::Core::Window::enableDepth();

    // =========================
    // LOAD MESH
    // =========================
    auto vertices = GFX::Core::Loader::loadOBJ("Assets/Objects/Cube.obj");

    // =========================
    // SHADER
    // =========================
    auto shader = GFX::Graphics::Shader::create("Assets/Shaders/vertex.glsl",
                                                "Assets/Shaders/fragment.glsl");

    // =========================
    // GPU OBJECTS
    // =========================
    GFX::Graphics::VertexArrayObject vao;
    GFX::Graphics::VertexBufferObject vbo;

    vbo.setData(vertices.data(), vertices.size() * sizeof(GFX::Core::Vertex));

    GFX::Graphics::VertexBufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(2); // uv
    layout.push<float>(3); // normal

    vao.addBuffer(vbo, layout);

    // =========================
    // MATRICES
    // =========================
    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1100.0f / 900.0f, 0.1f, 100.0f);

    // =========================
    // RENDER LOOP
    // =========================
    window->setOnFrameCallback(
        [&](float dt)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader->use();

            float time = static_cast<float>(glfwGetTime());

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, time * 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, time * 0.5f, glm::vec3(1.0f, 0.0f, 0.0f));

            shader->setMatrix4("uModel", model);
            shader->setMatrix4("uView", view);
            shader->setMatrix4("uProjection", projection);

            // light & color (обязательно для твоего fragment shader)
            shader->setVector3("uLightPos", glm::vec3(2.0f, 2.0f, 2.0f));
            shader->setVector3("uViewPos", glm::vec3(0.0f, 0.0f, 3.0f));
            shader->setVector3("uColor", glm::vec3(0.8f, 0.3f, 0.2f));

            vao.bind();

            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));

            vao.unbind();
        });

    window->runMainLoop();

    return 0;
}