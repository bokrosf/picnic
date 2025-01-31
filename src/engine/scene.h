#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

#include <functional>
#include <generator>
#include <map>
#include <queue>
#include <string>
#include <unordered_set>
#include <engine/component/component.h>
#include <engine/entity.h>
#include <engine/object_initializer.h>

class scene
{
public:
    virtual ~scene();
    virtual void initialize() = 0;
    int id() const;
    void update_root_status(entity &entity);
    void add(entity &entity);
    void add(component &component);
    void initialize_objects();
    void mark_as_destroyed(component &component);
    void mark_as_destroyed(entity &entity);
    void destroy_marked_objects();
    void reset();
    entity *find_entity(const std::string &name) const;
    entity *find_tagged_entity(const std::string &tag) const;
    std::generator<entity &> find_all_tagged_entity(const std::string &tag) const;
    std::generator<entity &> traverse(std::function<bool(const entity *entity)> filter) const;
protected:
    scene(int id);
private:
    void destroy_components();
    void destroy_entities();
    
    const int _id;
    std::unordered_set<entity *> _root_entities;
    std::unordered_set<entity *> _entities_with_destroyed_component;
    std::unordered_set<entity *> _entities_to_destroy;
    object_initializer _initializer;
    std::map<std::string, entity *> _named_entities;
};

#endif
