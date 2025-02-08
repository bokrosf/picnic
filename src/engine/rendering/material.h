#ifndef ENGINE_RENDERING_MATERIAL_H
#define ENGINE_RENDERING_MATERIAL_H

#include <string>
#include <SDL3/SDL.h>

struct material
{
    SDL_Color color;
    std::string texture_path;
};

#endif
