#include "ExternalLibs/GLM/glm/ext/matrix_transform.hpp"
#include "GFX/Core/Camera/include/Camera.h"
#include "GFX/Core/Window/include/Window.h"
#include "GFX/Graphics/Graphics/include/Material.h"
#include "GFX/Graphics/Graphics/include/Model.h"
#include "GFX/Graphics/Graphics/include/RenderContext.h"
#include "GFX/Graphics/Graphics/include/Sprite.h"
#include "GFX/Graphics/RawGraphics/include/Shader.h"

#include "ExternalLibs/GLM/glm//gtc/matrix_transform.hpp"
#include "ExternalLibs/GLM/glm/glm.hpp"
#include "GFX/Graphics/Graphics/include/Font.h"
#include "GFX/Graphics/Graphics/include/Text.h"
#include "GFX/Graphics/Graphics/include/Texture.h"

#include <memory>

int main()
{
    auto window = std::make_shared<GFX::Core::Window>(1100, 900, "Example");

    GFX::Core::Window::enableDepth();
    //window->setCursorCaptured(true);

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

    GFX::Core::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    camera.setPerspective(45.0f, 1100.0f / 900.0f, 0.1f, 100.0f);
    window->setCamera(camera);

    GFX::Core::Camera uiCamera(glm::vec3(0.0f, 0.0f, 1.0f));
    uiCamera.setOrthographic(0.0f, 1100.0f, 900.0f, 0.0f, 0.1f, 10.0f);

    auto font = GFX::Graphics::Font::create("Assets/Fonts/arial.TTF", 32);
    auto textShader = GFX::Graphics::Shader::create(
        "Assets/Shaders/text_vertex.glsl",
        "Assets/Shaders/text_fragment.glsl");
    auto spriteShader = GFX::Graphics::Shader::create(
        "Assets/Shaders/sprite_vertex.glsl",
        "Assets/Shaders/sprite_fragment.glsl");

    GFX::Graphics::Sprite sprite(texture, spriteShader);
    sprite.setPosition(20.0f, 90.0f, 0.0f);
    sprite.setSize(96.0f, 96.0f, 0.0f);

    GFX::Graphics::Text text(font, textShader, "Hello, World!");
    text.setPosition(20.0f, 40.0f, 0.0f);
    text.setColor(GFX::Graphics::Colors::Yellow);
    text.setOpacity(1.0f);
    text.setBold(true);

    GFX::Graphics::RenderContext render;


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

            render.clear(GFX::Graphics::Colors::Gray);

            float time = static_cast<float>(glfwGetTime());

            cube.setRotation(time * 30.0f, time * 60.0f, 0.0f);

            render.draw(cube, cubeMaterial, *activeCamera);
            render.draw(sprite, uiCamera);
            render.draw(text, uiCamera);

        });

    window->runMainLoop();

    return 0;
}
