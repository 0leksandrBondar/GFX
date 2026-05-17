#include "GFX/Core/BaseTypes/include/Transformable.h"

#include "ExternalLibs/GLM/glm/ext/matrix_transform.hpp"

namespace GFX::Core
{
    void Transformable::setPosition(const glm::vec3& position)
    {
        _position = position;
        _needsUpdate = true;
    }

    void Transformable::move(const glm::vec3& offset)
    {
        _position += offset;
        _needsUpdate = true;
    }

    void Transformable::setRotation(const glm::vec3& rotation)
    {
        _rotation = rotation;
        _needsUpdate = true;
    }

    void Transformable::setScale(const glm::vec3& scale)
    {
        _scale = scale;
        _needsUpdate = true;
    }

    void Transformable::setOrigin(const glm::vec3& origin)
    {
        _origin = origin;
        _originManuallySet = true;
        _needsUpdate = true;
    }

    void Transformable::setOriginToCenter()
    {
        _origin = _localBoundsMin + _size * 0.5f;
        _needsUpdate = true;
    }

    void Transformable::setLocalBounds(const glm::vec3& min, const glm::vec3& size)
    {
        _localBoundsMin = min;
        setSize(size.x, size.y, size.z);
    }

    void Transformable::setSize(const float width, const float height, const float depth)
    {
        const glm::vec3 newSize(width, height, depth);
        const bool hadSize = _size.x != 0.0f || _size.y != 0.0f || _size.z != 0.0f;

        if (_size.x != 0.0f && newSize.x != 0.0f)
            _scale.x *= newSize.x / _size.x;
        if (_size.y != 0.0f && newSize.y != 0.0f)
            _scale.y *= newSize.y / _size.y;
        if (_size.z != 0.0f && newSize.z != 0.0f)
            _scale.z *= newSize.z / _size.z;

        _size = newSize;

        if (!_originManuallySet && !hadSize)
            setOriginToCenter();

        _needsUpdate = true;
    }

    const glm::mat4& Transformable::getTransformMatrix() const
    {
        if (_needsUpdate)
            updateTransform();

        return _modelMatrix;
    }

    void Transformable::updateTransform() const
    {
        glm::mat4 transform(1.0f);

        transform = glm::translate(transform, _position);
        transform = glm::rotate(transform, glm::radians(_rotation.x), glm::vec3(1, 0, 0));
        transform = glm::rotate(transform, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
        transform = glm::rotate(transform, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
        transform = glm::scale(transform, _scale);
        transform = glm::translate(transform, -_origin);

        _modelMatrix = transform;
        _needsUpdate = false;
    }
} // namespace GFX::Core
