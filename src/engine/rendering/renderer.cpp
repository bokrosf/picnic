#include <engine/rendering/renderer.h>

renderer::renderer()
    : layer_order(0)
{
}

material *renderer::material()
{
    return _material.has_value() ? &_material.value() : nullptr;
}

void renderer::material(const ::material &material)
{
    _material.emplace(material);
}

bool renderer::use_material_color(SDL_Renderer *renderer)
{
    if (!_material)
    {
        return false;
    }

    const SDL_Color &color = _material->color;

    return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) == 0;
}

void renderer::use_color(SDL_Renderer *renderer, const SDL_Color &color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}