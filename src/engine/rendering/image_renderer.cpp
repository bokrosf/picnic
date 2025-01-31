#include <SDL2/SDL_image.h>
#include <engine/entity.h>
#include <engine/rendering/image_renderer.h>

image_renderer::image_renderer()
    : _texture(nullptr)
    , _texture_region(SDL_Rect{0, 0, 0, 0})
    , _draw_region(SDL_FRect{0, 0, 0, 0})
{
}

image_renderer::~image_renderer()
{
    unload_texture();
}

void image_renderer::render(SDL_Renderer *renderer)
{
    if (material() && !material()->texture_path.empty() && !_texture)
    {
        load_texture(renderer);
    }

    if (!_texture)
    {
        return;
    }

    glm::vec2 position = attached_to().transform().position() - glm::vec2(_texture_region.w / 2, _texture_region.h / 2);
    _draw_region.x = position.x;
    _draw_region.y = position.y;
    SDL_RenderCopyF(renderer, _texture, &_texture_region, &_draw_region);
}

void image_renderer::load_texture(SDL_Renderer *renderer)
{
    unload_texture();
    
    if (_texture = IMG_LoadTexture(renderer, material()->texture_path.c_str()))
    {
        SDL_QueryTexture(_texture, nullptr, nullptr, &_texture_region.w, &_texture_region.h);
        _draw_region.w = _texture_region.w;
        _draw_region.h = _texture_region.h;
    }
}

void image_renderer::unload_texture()
{
    if (!_texture)
    {
        return;
    }
    
    SDL_DestroyTexture(_texture);
    _texture = nullptr;
}
