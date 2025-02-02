#ifndef ENGINE_APP_H
#define ENGINE_APP_H

#include <engine/app_configuration.h>
#include <engine/app_event.h>
#include <engine/component_added.h>
#include <engine/component_destroyed.h>
#include <engine/entity_created.h>
#include <engine/entity_destroyed.h>
#include <engine/entity_parent_changed.h>
#include <engine/scene/scene_destroyed.h>

class app
{
public:
    virtual ~app();
    void run();
protected:
    app(const app_configuration &configuration);
    virtual void load_start_scene() = 0;
private:
    void initialize_subsystems();
    void shutdown();
    void handle_user_input();
    void handle_app_event(const app_event &message);
    void create_entity(const entity_created &message);
    void destroy_entity(const entity_destroyed &message);
    void add_component(const component_added &message);
    void destroy_component(const component_destroyed &message);
    void change_entity_parent(const entity_parent_changed &message);
    void destroy_scene(const scene_destroyed &message);
        
    const app_configuration _configuration;
    bool _running;
};

#endif
