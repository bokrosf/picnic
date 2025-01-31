#include <engine/collision/box_collider.h>

box_collider::box_collider()
    : box_collider(glm::vec2(0, 0))
{
}

box_collider::box_collider(const glm::vec2 &area)
    : _area(area)
{
}

const glm::vec2 &box_collider::area() const
{
    return _area;
}

void box_collider::area(const glm::vec2 area)
{
    _area = area;
}
