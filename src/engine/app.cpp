#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <engine/app.h>
#include <engine/display.h>
#include <engine/time/game_time.h>
#include <engine/input.h>
#include <engine/messaging/messenger.h>
#include <engine/scene_loader.h>
#include <engine/subsystem_initialization_failed.h>

app::app(const app_configuration &configuration)
    : _configuration(configuration)
    , _running(false)
{
}

app::~app()
{
    shutdown();
}

void app::run()
{
    initialize_subsystems();
    messenger::subscribe<app_event>(*this);
    messenger::subscribe<entity_created>(*this);
    messenger::subscribe<entity_destroyed>(*this);
    messenger::subscribe<component_added>(*this);
    messenger::subscribe<component_destroyed>(*this);
    messenger::subscribe<entity_parent_changed>(*this);
    messenger::subscribe<scene_destroyed>(*this);
    load_start_scene();
    scene_loader::commit();
    game_time::reset(scene_loader::active().id());
    _running = true;
    
    while (_running)
    {
        const int original_scene_id = scene_loader::active().id();
        scene_loader::active().initialize_objects();
        _collision_engine.detect_collisions(scene_loader::active());
        input::read_events();
        handle_user_input();
        _gameplay_engine.update(scene_loader::active());
        scene_loader::active().destroy_marked_objects();
        _rendering_engine.render(scene_loader::active());
        scene_loader::commit();

        if (scene_loader::active().id() == original_scene_id)
        {
            game_time::end_frame();
        }
        else
        {
            game_time::reset(scene_loader::active().id());
        }
    }

    shutdown();
}

void app::receive(const app_event &message)
{
    if (message == app_event::exit_requested)
    {
        _running = false;
    }
}

void app::receive(const entity_created &message)
{
    scene_loader::active().add(message.created);
}

void app::receive(const entity_destroyed &message)
{
    scene_loader::active().mark_as_destroyed(message.entity);
}

void app::receive(const component_added &message)
{
    scene_loader::active().add(message.added);
}

void app::receive(const component_destroyed &message)
{
    scene_loader::active().mark_as_destroyed(message.component);
}

void app::receive(const entity_parent_changed &message)
{
    scene_loader::active().update_root_status(message.entity);
}

void app::receive(const scene_destroyed &message)
{
    game_time::erase(message.id);
}

void app::initialize_subsystems()
{
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_EVENTS | SDL_INIT_VIDEO) != 0)
    {
        throw subsystem_initialization_failed(std::string("SDL initialization failed.").append(SDL_GetError()));
    }

    int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;

    if (int initialized_flags = IMG_Init(img_flags); initialized_flags != img_flags)
    {
        throw subsystem_initialization_failed(
            std::string("SDL Image initilaization failed. requested: ")
                .append(std::to_string(img_flags))
                .append("initialized: ")
                .append(std::to_string(initialized_flags)));
    }

    display::initialize(_configuration.title);
    scene_loader::initialize();
    _rendering_engine.initialize(display::window());
}

void app::shutdown()
{
    messenger::unsubscribe<app_event>(*this);
    messenger::unsubscribe<entity_created>(*this);
    messenger::unsubscribe<entity_destroyed>(*this);
    messenger::unsubscribe<component_added>(*this);
    messenger::unsubscribe<component_destroyed>(*this);
    messenger::unsubscribe<entity_parent_changed>(*this);
    messenger::unsubscribe<scene_destroyed>(*this);
    _rendering_engine.shutdown();
    scene_loader::shutdown();
    display::shutdown();
    IMG_Quit();
    SDL_Quit();
}

void app::handle_user_input()
{
    if (input::occured(SDL_QUIT))
    {
        _running = false;
    }
}
