#pragma once

#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

namespace GFX::Core
{
    class Transformable
    {
    public:
        Transformable() = default;
        virtual ~Transformable() = default;

        // POSITION
        void setPosition(float x, float y, float z) { setPosition(glm::vec3(x, y, z)); }
        void setPosition(const glm::vec3& position);

        void move(float x, float y, float z);

        // ROTATION (в градусах)
        void setRotation(float x, float y, float z);
        void setRotation(const glm::vec3& rotation);

        // SCALE
        void setScale(float x, float y, float z) { setScale(glm::vec3(x, y, z)); }
        void setScale(const glm::vec3& scale);

        // ORIGIN
        void setOrigin(const glm::vec3& origin);
        void setOrigin(float x, float y, float z) { setOrigin(glm::vec3(x, y, z)); }

        void setOriginToCenter();

        void setSize(float width, float height, float depth);

        // GETTERS
        [[nodiscard]] glm::vec3 getPosition() const noexcept { return _position; }
        [[nodiscard]] glm::vec3 getRotation() const noexcept { return _rotation; }
        [[nodiscard]] glm::vec3 getScale() const noexcept { return _scale; }
        [[nodiscard]] glm::vec3 getSize() const noexcept { return _size; }
        [[nodiscard]] glm::vec3 getOrigin() const noexcept { return _origin; }

        [[nodiscard]] const glm::mat4& getTransformMatrix();

    protected:
        bool _originManuallySet{ false };

        glm::vec3 _position{ 0.f };
        glm::vec3 _rotation{ 0.f };
        glm::vec3 _scale{ 1.f };
        glm::vec3 _size{ 0.f };
        glm::vec3 _origin{ 0.f };

    private:
        glm::mat4 _modelMatrix{ 1.0f };
        bool _needsUpdate{ true };

        void updateTransform();
    };

} // namespace GFX::Core