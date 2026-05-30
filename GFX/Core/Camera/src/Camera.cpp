#include "GFX/Core/Camera/include/Camera.h"

#include "ExternalLibs/GLM/glm/ext/matrix_clip_space.hpp"
#include "ExternalLibs/GLM/glm/ext/matrix_transform.hpp"
#include "ExternalLibs/GLM/glm/geometric.hpp"
#include "ExternalLibs/GLM/glm/trigonometric.hpp"

#include <algorithm>
#include <cmath>

namespace GFX::Core
{
    Camera::Camera(const glm::vec3& position) : _position(position)
    {
        updateDirection();
    }

    void Camera::move(const glm::vec3& offset)
    {
        _position += offset;
    }

    void Camera::rotate(const float yawOffset, const float pitchOffset)
    {
        _yaw += yawOffset;
        _pitch += pitchOffset;
        _pitch = std::clamp(_pitch, -89.0f, 89.0f);
        updateDirection();
    }

    void Camera::setRotation(const float yaw, const float pitch)
    {
        _yaw = yaw;
        _pitch = std::clamp(pitch, -89.0f, 89.0f);
        updateDirection();
    }

    void Camera::setWorldUp(const glm::vec3& worldUp)
    {
        _worldUp = glm::normalize(worldUp);
        updateDirection();
    }

    glm::mat4 Camera::getViewMatrix() const
    {
        return glm::lookAt(_position, _position + _front, _up);
    }

    glm::mat4 Camera::getProjectionMatrix() const
    {
        if (_projectionMode == CameraProjectionMode::Orthographic)
        {
            return glm::ortho(_orthographicLeft, _orthographicRight, _orthographicBottom,
                              _orthographicTop, _nearPlane, _farPlane);
        }

        return glm::perspective(glm::radians(_verticalFovDegrees), _aspectRatio, _nearPlane,
                                _farPlane);
    }

    void Camera::setClipPlanes(const float nearPlane, const float farPlane)
    {
        _nearPlane = nearPlane;
        _farPlane = farPlane;
    }

    void Camera::setPerspective(const float verticalFovDegrees, const float aspectRatio,
                                const float nearPlane, const float farPlane)
    {
        _projectionMode = CameraProjectionMode::Perspective;
        _verticalFovDegrees = verticalFovDegrees;
        _aspectRatio = aspectRatio;
        setClipPlanes(nearPlane, farPlane);
    }

    void Camera::setOrthographic(const float verticalSize, const float aspectRatio,
                                 const float nearPlane, const float farPlane)
    {
        _projectionMode = CameraProjectionMode::Orthographic;
        _orthographicVerticalSize = verticalSize;
        _aspectRatio = aspectRatio;
        const float halfHeight = _orthographicVerticalSize * 0.5f;
        const float halfWidth = halfHeight * _aspectRatio;
        _orthographicLeft = -halfWidth;
        _orthographicRight = halfWidth;
        _orthographicBottom = -halfHeight;
        _orthographicTop = halfHeight;
        setClipPlanes(nearPlane, farPlane);
    }

    void Camera::setOrthographic(const float left, const float right, const float bottom,
                                 const float top, const float nearPlane, const float farPlane)
    {
        _projectionMode = CameraProjectionMode::Orthographic;
        _orthographicLeft = left;
        _orthographicRight = right;
        _orthographicBottom = bottom;
        _orthographicTop = top;
        _orthographicVerticalSize = std::abs(top - bottom);
        _aspectRatio = std::abs((right - left) / (top - bottom));
        setClipPlanes(nearPlane, farPlane);
    }

    void Camera::updateDirection()
    {
        glm::vec3 direction;
        direction.x = std::cos(glm::radians(_yaw)) * std::cos(glm::radians(_pitch));
        direction.y = std::sin(glm::radians(_pitch));
        direction.z = std::sin(glm::radians(_yaw)) * std::cos(glm::radians(_pitch));

        _front = glm::normalize(direction);
        _right = glm::normalize(glm::cross(_front, _worldUp));
        _up = glm::normalize(glm::cross(_right, _front));
    }
} // namespace GFX::Core
