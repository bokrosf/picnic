#ifndef ENGINE_COMPONENT_TRANSFORM_H
#define ENGINE_COMPONENT_TRANSFORM_H

#include <glm/vec2.hpp>
#include <engine/component/component.h>

class transform : public component
{
public:
    const glm::vec2 &position() const;
    void position(const glm::vec2 &position);
    void translate(const glm::vec2 &translation);
    const glm::vec2 &scale() const;
    void scale(const glm::vec2 &scale);
private:
    glm::vec2 _position;
    glm::vec2 _scale;
};

#endif
