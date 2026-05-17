#pragma once

#include "ExternalLibs/GLM/glm/mat4x4.hpp"
#include "ExternalLibs/GLM/glm/vec3.hpp"

namespace GFX::Core
{
    enum class CameraProjectionMode
    {
        Perspective,
        Orthographic
    };

    class Camera final
    {
    public:
        explicit Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 3.0f));

        void move(const glm::vec3& offset);
        void rotate(float yawOffset, float pitchOffset);

        [[nodiscard]] glm::mat4 getViewMatrix() const;
        [[nodiscard]] glm::mat4 getProjectionMatrix() const;
        [[nodiscard]] CameraProjectionMode getProjectionMode() const { return _projectionMode; }
        [[nodiscard]] const glm::vec3& getPosition() const { return _position; }
        [[nodiscard]] const glm::vec3& getFront() const { return _front; }
        [[nodiscard]] const glm::vec3& getRight() const { return _right; }
        [[nodiscard]] const glm::vec3& getUp() const { return _up; }
        [[nodiscard]] const glm::vec3& getWorldUp() const { return _worldUp; }
        [[nodiscard]] float getYaw() const { return _yaw; }
        [[nodiscard]] float getPitch() const { return _pitch; }

        void setPosition(const glm::vec3& position) { _position = position; }
        void setRotation(float yaw, float pitch);
        void setWorldUp(const glm::vec3& worldUp);
        void setAspectRatio(float aspectRatio) { _aspectRatio = aspectRatio; }
        void setClipPlanes(float nearPlane, float farPlane);
        void setPerspective(float verticalFovDegrees, float aspectRatio, float nearPlane,
                            float farPlane);
        void setOrthographic(float verticalSize, float aspectRatio, float nearPlane,
                             float farPlane);

    private:
        void updateDirection();

    private:
        glm::vec3 _position;
        glm::vec3 _front{ 0.0f, 0.0f, -1.0f };
        glm::vec3 _worldUp{ 0.0f, 1.0f, 0.0f };
        glm::vec3 _right{ 1.0f, 0.0f, 0.0f };
        glm::vec3 _up{ 0.0f, 1.0f, 0.0f };

        float _yaw{ -90.0f };
        float _pitch{ 0.0f };

        CameraProjectionMode _projectionMode{ CameraProjectionMode::Perspective };
        float _verticalFovDegrees{ 45.0f };
        float _orthographicVerticalSize{ 10.0f };
        float _aspectRatio{ 16.0f / 9.0f };
        float _nearPlane{ 0.1f };
        float _farPlane{ 100.0f };
    };
} // namespace GFX::Core
