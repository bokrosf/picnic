#ifndef ENGINE_OBJECTINITIALIZER_H
#define ENGINE_OBJECTINITIALIZER_H

#include <unordered_set>
#include <engine/component/component.h>
#include <engine/entity.h>

class object_initializer
{
public:
    void add(entity &entity);
    void add(component &component);
    void initialize_objects();
private:
    void initialize_entities();
    void initialize_components();

    std::unordered_set<entity *> _initialized_entities;
    std::unordered_set<entity *> _scheduled_entities;
    std::unordered_set<component *> _initialized_components;
    std::unordered_set<component *> _scheduled_components;
};

#endif
