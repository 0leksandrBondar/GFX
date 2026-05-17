#pragma once

#include "ExternalLibs/GLM/glm/mat4x4.hpp"
#include "ExternalLibs/GLM/glm/vec3.hpp"

namespace GFX::Core
{
    class Transformable
    {
    public:
        Transformable() = default;
        virtual ~Transformable() = default;

        void setPosition(float x, float y, float z) { setPosition(glm::vec3(x, y, z)); }
        void setPosition(const glm::vec3& position);

        void move(float x, float y, float z) { move(glm::vec3(x, y, z)); }
        void move(const glm::vec3& offset);

        void setRotation(float x, float y, float z) { setRotation(glm::vec3(x, y, z)); }
        void setRotation(const glm::vec3& rotation);

        void setScale(float x, float y, float z) { setScale(glm::vec3(x, y, z)); }
        void setScale(const glm::vec3& scale);

        void setOrigin(float x, float y, float z) { setOrigin(glm::vec3(x, y, z)); }
        void setOrigin(const glm::vec3& origin);
        void setOriginToCenter();

        void setSize(float width, float height, float depth);
        void setLocalBounds(const glm::vec3& min, const glm::vec3& size);

        [[nodiscard]] glm::vec3 getPosition() const noexcept { return _position; }
        [[nodiscard]] glm::vec3 getRotation() const noexcept { return _rotation; }
        [[nodiscard]] glm::vec3 getScale() const noexcept { return _scale; }
        [[nodiscard]] glm::vec3 getSize() const noexcept { return _size; }
        [[nodiscard]] glm::vec3 getOrigin() const noexcept { return _origin; }

        [[nodiscard]] const glm::mat4& getTransformMatrix() const;

    protected:
        bool _originManuallySet{ false };

        glm::vec3 _position{ 0.0f };
        glm::vec3 _rotation{ 0.0f };
        glm::vec3 _scale{ 1.0f };
        glm::vec3 _size{ 0.0f };
        glm::vec3 _origin{ 0.0f };
        glm::vec3 _localBoundsMin{ 0.0f };

    private:
        void updateTransform() const;

    private:
        mutable glm::mat4 _modelMatrix{ 1.0f };
        mutable bool _needsUpdate{ true };
    };
} // namespace GFX::Core
