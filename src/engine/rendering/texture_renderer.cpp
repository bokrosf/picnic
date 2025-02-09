#include <engine/assett.h>
#include <engine/component/transform.h>
#include <engine/rendering/texture_renderer.h>

void texture_renderer::render(SDL_Renderer *renderer)
{
    if (!material() || !material()->texture)
    {
        return;
    }

    SDL_Texture *loaded_texture = assett::texture(material()->texture->id);

    if (!loaded_texture)
    {
        return;
    }

    SDL_FRect target_area;
    target_area.w = material()->texture->scale.x * loaded_texture->w;
    target_area.h = material()->texture->scale.y * loaded_texture->h;
    target_area.x = transform().position().x - (0.5F * target_area.w);
    target_area.y = transform().position().y - (0.5F * target_area.h);

    SDL_RenderTexture(renderer, loaded_texture, nullptr, &target_area);
}
