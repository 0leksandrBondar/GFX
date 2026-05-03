#include "GFX/Core/BaseTypes/include/Transformable.h"

#include "glm/ext/matrix_transform.hpp"

namespace GFX::Core
{
    void Transformable::setPosition(const glm::vec3& position)
    {
        _position = position;
        _needsUpdate = true;
    }

    void Transformable::move(const float x, const float y, const float z)
    {
        _position += glm::vec3(x, y, z);
        _needsUpdate = true;
    }

    void Transformable::setRotation(const glm::vec3& rotation)
    {
        _rotation = rotation;
        _needsUpdate = true;
    }

    void Transformable::setRotation(const float x, const float y, const float z)
    {
        setRotation(glm::vec3(x, y, z));
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
        _origin = _size * 0.5f;
        _needsUpdate = true;
    }

    void Transformable::setSize(const float width, const float height, const float depth)
    {
        _size = glm::vec3(width, height, depth);

        if (!_originManuallySet)
            setOriginToCenter();

        _needsUpdate = true;
    }

    const glm::mat4& Transformable::getTransformMatrix()
    {
        if (_needsUpdate)
            updateTransform();

        return _modelMatrix;
    }

    void Transformable::updateTransform()
    {
        glm::mat4 transform(1.0f);

        // translate
        transform = glm::translate(transform, _position);

        // pivot (origin)
        transform = glm::translate(transform, _origin);

        // rotation
        transform = glm::rotate(transform, glm::radians(_rotation.x), glm::vec3(1, 0, 0));
        transform = glm::rotate(transform, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
        transform = glm::rotate(transform, glm::radians(_rotation.z), glm::vec3(0, 0, 1));

        // scale
        transform = glm::scale(transform, _scale);

        // обратно от origin
        transform = glm::translate(transform, -_origin);

        _modelMatrix = transform;
        _needsUpdate = false;
    }

} // namespace GFX::Core