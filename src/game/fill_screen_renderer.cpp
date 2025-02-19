#include <game/fill_screen_renderer.h>

void fill_screen_renderer::render(SDL_Renderer *renderer)
{
    if (use_material_color(renderer))
    {
        SDL_RenderClear(renderer);
    }
}
