#pragma once

#include "GFX/Core/Camera/include/Camera.h"
#include "GFX/Graphics/Graphics/include/Material.h"
#include "GFX/Graphics/Graphics/include/Model.h"
#include "GFX/Graphics/RawGraphics/include/Shader.h"

namespace GFX::Graphics
{
    class Renderer final
    {
    public:
        void draw(const Model& model, const Material& material, const Core::Camera& camera) const;
        void draw(const Model& model, const Shader& shader, const Core::Camera& camera) const;
    };
} // namespace GFX::Graphics
