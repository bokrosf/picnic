#include <engine/component/initializable.h>
#include <engine/component/startable.h>
#include <engine/object_initializer.h>

void object_initializer::add(entity &entity)
{
    _scheduled_entities.insert(&entity);
}

void object_initializer::add(component &component)
{
    _scheduled_components.insert(&component);
}

void object_initializer::initialize_objects()
{
    while (!_scheduled_entities.empty() || !_scheduled_components.empty())
    {
        initialize_entities();
        initialize_components();
    }
}

void object_initializer::initialize_entities()
{
    if (_scheduled_entities.empty())
    {
        return;
    }

    _scheduled_entities.swap(_initialized_entities);

    for (auto entity : _initialized_entities)
    {
        entity->_life_state = life_state::alive;
    }

    _initialized_entities.clear();
}

void object_initializer::initialize_components()
{
    if (_scheduled_components.empty())
    {
        return;
    }

    _scheduled_components.swap(_initialized_components);
    auto initializable_cast = [](component *c) { return dynamic_cast<initializable *>(c); };
    auto startable_cast = [](component *c) { return dynamic_cast<startable *>(c); };

    for (auto c : _initialized_components | std::views::filter(initializable_cast) | std::views::transform(initializable_cast))
    {
        c->initialize();
    }

    for (auto c : _initialized_components | std::views::filter(startable_cast) | std::views::transform(startable_cast))
    {
        c->start();
    }

    for (auto c : _initialized_components)
    {
        c->_life_state = life_state::alive;
    }

    _initialized_components.clear();
}
