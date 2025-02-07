#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <engine/activatable.h>
#include <engine/collision/box_collider.h>
#include <engine/collision/collision.h>
#include <engine/collision/collision_engine.h>
#include <engine/collision/collision_handler.h>
#include <engine/entity.h>

namespace
{
    std::vector<box_collider *> collect_colliders(const scene &scene)
    {
        std::vector<box_collider *> colliders;
        auto filter_entity = [](const entity *e) { return e->active() && e->life_state() == life_state::alive; };

        for (const entity &entity : scene.traverse(filter_entity))
        {
            auto collider_filter = [](box_collider *c) { return c->active() && c->life_state() == life_state::alive; };

            for (box_collider *c : entity.all_attached_components<box_collider>() | std::views::filter(collider_filter))
            {
                colliders.push_back(c);
            }
        }

        return colliders;
    }

    void notify_collided_entities(box_collider &collider, const std::unordered_set<entity *> &collided_entities)
    {
        collision collision{collider};

        for (entity *collided_with : collided_entities)
        {
            for (component *c : collided_with->all_attached_components<component>())
            {
                collision_handler *handler = dynamic_cast<collision_handler *>(c);
                activatable *activatable = dynamic_cast<::activatable *>(c);
                
                if (handler && (!activatable || activatable->active()))
                {
                    handler->collide(collision);
                }
            }
        }
    }
}

namespace collision_engine
{
    void detect_collisions(const scene &scene)
    {
        std::vector<box_collider *> colliders = collect_colliders(scene);

        for (box_collider *current : colliders)
        {
            std::unordered_set<entity *> collided_entities;

            for (box_collider *other : colliders | std::views::filter([current](box_collider *c) { return c != current; }))
            {
                glm::vec2 difference = other->transform().position() - current->transform().position();
                float x_threshold = std::abs(current->area().x) + std::abs(other->area().x);
                float y_threshold = std::abs(current->area().y) + std::abs(other->area().y);

                if (std::abs(difference.x) < x_threshold && std::abs(difference.y) < y_threshold)
                {
                    collided_entities.insert(&other->attached_to());
                }
            }

            notify_collided_entities(*current, collided_entities);
        }
    }
}
