#ifndef ENGINE_APP_H
#define ENGINE_APP_H

#include <engine/app_configuration.h>
#include <engine/app_event.h>
#include <engine/component_added.h>
#include <engine/component_destroyed.h>
#include <engine/entity_created.h>
#include <engine/entity_destroyed.h>
#include <engine/entity_parent_changed.h>
#include <engine/messaging/recipient.h>
#include <engine/scene/scene_destroyed.h>

class app : 
    public recipient<app_event>,
    public recipient<entity_created>,
    public recipient<entity_destroyed>,
    public recipient<component_added>,
    public recipient<component_destroyed>,
    public recipient<entity_parent_changed>,
    public recipient<scene_destroyed>
{
public:
    virtual ~app();
    void run();
    void receive(const app_event &message) final;
    void receive(const entity_created &message) final;
    void receive(const entity_destroyed &message) final;
    void receive(const component_added &message) final;
    void receive(const component_destroyed &message) final;
    void receive(const entity_parent_changed &message) final;
    void receive(const scene_destroyed &message) final;
protected:
    app(const app_configuration &configuration);
    virtual void load_start_scene() = 0;
private:
    void initialize_subsystems();
    void shutdown();
    void handle_user_input();
        
    const app_configuration _configuration;
    bool _running;
};

#endif
