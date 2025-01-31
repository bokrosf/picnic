#ifndef ENGINE_COLLISION_COLLISIONENGINE_H
#define ENGINE_COLLISION_COLLISIONENGINE_H

#include <unordered_set>
#include <engine/collision/box_collider.h>
#include <engine/collision/collision_handler.h>
#include <engine/entity.h>
#include <engine/scene.h>

class collision_engine
{
public:
    void detect_collisions(const scene &scene);
private:
    std::vector<box_collider *> collect_colliders(const scene &scene) const;
    void notify_collided_entities(box_collider &collider, const std::unordered_set<entity *> &collided_entities) const;
};

#endif
