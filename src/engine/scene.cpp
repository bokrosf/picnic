#include <queue>
#include <utility>
#include <engine/component/initializable.h>
#include <engine/component/startable.h>
#include <engine/entity.h>
#include <engine/entity_name_collision.h>
#include <engine/life_state.h>
#include <engine/scene.h>

scene::scene(int id)
    : _id(id)
{
}

scene::~scene()
{
    for (auto root : _root_entities)
    {
        delete root;
    }
}

int scene::id() const
{
    return _id;
}

void scene::update_root_status(entity &entity)
{
    if (entity.parent())
    {
        _root_entities.erase(&entity);
    }
    else
    {
        _root_entities.insert(&entity);
    }
}

void scene::add(entity &entity)
{
    if (!entity.name().empty() && !_named_entities.insert(std::make_pair(entity.name(), &entity)).second)
    {
        throw entity_name_collision(std::string("Already exists an entity with name: ").append(entity.name()));
    }
    
    _initializer.add(entity);
    update_root_status(entity);
    entity._scene = this;
}

void scene::add(component &component)
{
    _initializer.add(component);
}

void scene::initialize_objects()
{
    _initializer.initialize_objects();
}

void scene::mark_as_destroyed(entity &entity)
{
    _entities_to_destroy.insert(&entity);
}

void scene::mark_as_destroyed(component &component)
{
    _entities_with_destroyed_component.insert(&component.attached_to());
}

void scene::destroy_marked_objects()
{
    destroy_components();
    destroy_entities();
}

entity *scene::find_entity(const std::string &name) const
{
    auto it = _named_entities.find(name);

    return it != _named_entities.end() ? it->second : nullptr;
}

entity *scene::find_tagged_entity(const std::string &tag) const
{
    auto filter = [&tag](const entity *e) { return e->tag() == tag; };

    for (entity &e : traverse(filter))
    {
        return &e;
    }

    return nullptr;
}

std::generator<entity &> scene::find_all_tagged_entity(const std::string &tag) const
{
    auto filter = [&tag](const entity *e) { return e->tag() == tag; };

    for (entity &e : traverse(filter))
    {
        co_yield e;
    }
}

std::generator<entity &> scene::traverse(std::function<bool(const entity *entity)> filter) const
{
    std::queue<entity *> entities;

    for (entity *root : _root_entities | std::views::filter(filter))
    {
        entities.push(root);
    }

    while (!entities.empty())
    {
        entity *current = entities.front();
        entities.pop();

        co_yield *current;

        for (entity *child : current->children() | std::views::filter(filter))
        {
            entities.push(child);
        }
    }
}

void scene::reset()
{
    for (auto e : _root_entities)
    {
        delete e;
    }

    _root_entities.clear();
    _entities_with_destroyed_component.clear();
    _entities_to_destroy.clear();
    _initializer = object_initializer();
    _named_entities.clear();

    initialize();
}

void scene::destroy_components()
{
    for (entity *entity : _entities_with_destroyed_component)
    {
        if (!_entities_to_destroy.contains(entity))
        {
            entity->erase_destroyed_components();
        }
    }
    
    _entities_with_destroyed_component.clear();
}

void scene::destroy_entities()
{
    for (auto destroyed : _entities_to_destroy)
    {
        destroyed->attach_to(nullptr);
        
        if (!destroyed->name().empty())
        {
            _named_entities.erase(destroyed->name());
        }
    }

    for (auto destroyed : _entities_to_destroy)
    {
        _root_entities.erase(destroyed);
    }

    for (auto destroyed : _entities_to_destroy)
    {
        delete destroyed;
    }

    _entities_to_destroy.clear();
}
