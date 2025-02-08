#ifndef ENGINE_RENDERING_RENDERINGENGINE_H
#define ENGINE_RENDERING_RENDERINGENGINE_H

#include <SDL3/SDL.h>
#include <engine/scene/scene.h>

namespace rendering_engine
{
    void initialize(SDL_Window &window);
    void shutdown();
    void render(const scene &scene);
};

#endif
