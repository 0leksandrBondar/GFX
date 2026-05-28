#include "ExternalLibs/GLM/glm/ext/matrix_transform.hpp"
#include "GFX/Core/Camera/include/Camera.h"
#include "GFX/Core/Window/include/Window.h"
#include "GFX/Graphics/Graphics/include/Material.h"
#include "GFX/Graphics/Graphics/include/Model.h"
#include "GFX/Graphics/Graphics/include/Renderer.h"
#include "GFX/Graphics/RawGraphics/include/Shader.h"

#include "ExternalLibs/GLM/glm//gtc/matrix_transform.hpp"
#include "ExternalLibs/GLM/glm/glm.hpp"
#include "GFX/Graphics/Graphics/include/Texture.h"

#include <memory>

int main()
{
    auto window = std::make_shared<GFX::Core::Window>(1100, 900, "Example");

    GFX::Core::Window::enableDepth();
    window->setCursorCaptured(true);

    // =========================
    // SHADER
    // =========================
    auto shader = GFX::Graphics::Shader::create("Assets/Shaders/vertex.glsl",
                                                "Assets/Shaders/fragment.glsl");

    // =========================
    // TEXTURE
    // =========================
    auto texture = GFX::Graphics::Texture::create("Assets/Textures/Cube.png");
    GFX::Graphics::Material cubeMaterial(shader);
    cubeMaterial.setTexture("uTexture", texture);
    cubeMaterial.setVector3("uLightPos", glm::vec3(2.0f, 2.0f, 2.0f));
    cubeMaterial.setVector3("uColor", glm::vec3(0.8f, 0.3f, 0.2f));

    auto cube = GFX::Graphics::Model::load("Assets/Objects/Cube.obj");

    cube.setScale(1.0f, 1.0f, 1.0f);
    GFX::Graphics::Renderer renderer;

    GFX::Core::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    camera.setPerspective(45.0f, 1100.0f / 900.0f, 0.1f, 100.0f);
    window->setCamera(camera);


    // =========================
    // RENDER LOOP
    // =========================
    window->setOnFrameCallback(
        [&](float dt)
        {
            auto& input = window->getInput();
            if (input.isKeyDown(GLFW_KEY_ESCAPE))
                window->close();

            const GFX::Core::Camera* activeCamera = window->getCamera();
            if (!activeCamera)
                return;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            float time = static_cast<float>(glfwGetTime());

            cube.setRotation(time * 30.0f, time * 60.0f, 0.0f);
            renderer.draw(cube, cubeMaterial, *activeCamera);
        });

    window->runMainLoop();

    return 0;
}
