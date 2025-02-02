#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <engine/app.h>
#include <engine/collision/collision_engine.h>
#include <engine/display.h>
#include <engine/time/game_time.h>
#include <engine/input.h>
#include <engine/gameplay_engine.h>
#include <engine/messaging/messenger.h>
#include <engine/rendering/rendering_engine.h>
#include <engine/scene/scene_loader.h>
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
    messenger::subscribe(this, &app::handle_app_event);
    messenger::subscribe(this, &app::create_entity);
    messenger::subscribe(this, &app::destroy_entity);
    messenger::subscribe(this, &app::add_component);
    messenger::subscribe(this, &app::destroy_component);
    messenger::subscribe(this, &app::change_entity_parent);
    messenger::subscribe(this, &app::destroy_scene);
    load_start_scene();
    scene_loader::commit();
    game_time::reset(scene_loader::active().id());
    _running = true;
    
    while (_running)
    {
        const int original_scene_id = scene_loader::active().id();
        scene_loader::active().initialize_objects();
        collision_engine::detect_collisions(scene_loader::active());
        input::read_events();
        handle_user_input();
        gameplay_engine::update(scene_loader::active());
        scene_loader::active().destroy_marked_objects();
        rendering_engine::render(scene_loader::active());
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
    rendering_engine::initialize(display::window());
    scene_loader::initialize();
}

void app::shutdown()
{
    messenger::unsubscribe_all(this);
    scene_loader::shutdown();
    rendering_engine::shutdown();
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

void app::handle_app_event(const app_event &message)
{
    if (message == app_event::exit_requested)
    {
        _running = false;
    }
}

void app::create_entity(const entity_created &message)
{
    scene_loader::active().add(message.created);
}

void app::destroy_entity(const entity_destroyed &message)
{
    scene_loader::active().mark_as_destroyed(message.entity);
}

void app::add_component(const component_added &message)
{
    scene_loader::active().add(message.added);
}

void app::destroy_component(const component_destroyed &message)
{
    scene_loader::active().mark_as_destroyed(message.component);
}

void app::change_entity_parent(const entity_parent_changed &message)
{
    scene_loader::active().update_root_status(message.entity);
}

void app::destroy_scene(const scene_destroyed &message)
{
    game_time::erase(message.id);
}
