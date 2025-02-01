#ifndef ENGINE_COLLISION_BOXCOLLIDER_H
#define ENGINE_COLLISION_BOXCOLLIDER_H

#include <glm/vec2.hpp>
#include <engine/component/behavior.h>

class box_collider : public behavior
{
public:
    box_collider();
    box_collider(const glm::vec2 &area);
    const glm::vec2 &area() const;
    void area(const glm::vec2 area);
private:
    glm::vec2 _area;
};

#endif
