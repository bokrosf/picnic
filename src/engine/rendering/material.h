#ifndef ENGINE_RENDERING_MATERIAL_H
#define ENGINE_RENDERING_MATERIAL_H

#include <optional>
#include <SDL3/SDL.h>
#include <engine/rendering/texture.h>

struct material
{
    SDL_Color color;
    std::optional<::texture> texture;
};

#endif
