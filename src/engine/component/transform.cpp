#include <engine/component/transform.h>

const glm::vec2 &transform::position() const
{
    return _position;
}

void transform::position(const glm::vec2 &position)
{
    _position = position;
}

void transform::translate(const glm::vec2 &translation)
{
    _position += translation;
}

const glm::vec2 &transform::scale() const
{
    return _scale;
}

void transform::scale(const glm::vec2 &scale)
{
    _scale = scale;
}
