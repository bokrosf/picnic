#include <game/fill_screen_renderer.h>
#include <game/scene/game_ending_scene.h>

game_ending_scene::game_ending_scene(scene::id_type id, game_ending ending)
    : scene(id)
    , _ending(ending)
{
}

void game_ending_scene::initialize()
{
    entity &e = entity::create();
    renderer &r = e.add_component<fill_screen_renderer>();
    SDL_Color color{0, 0, 0, 0};

    switch (_ending)
    {
        case game_ending::baskets_collected:
            color = SDL_Color{0, 255, 0, 255};
            break;
        case game_ending::player_detected:
            color = SDL_Color{255, 0, 0, 255};
            break;
    }

    r.material(material{.color = color});
}
