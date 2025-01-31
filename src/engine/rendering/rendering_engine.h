#ifndef ENGINE_RENDERING_RENDERINGENGINE_H
#define ENGINE_RENDERING_RENDERINGENGINE_H

#include <string>
#include <SDL2/SDL.h>
#include <engine/scene.h>

class rendering_engine
{
public:
    rendering_engine();
    ~rendering_engine();
    void initialize(SDL_Window &window);
    void shutdown();
    void render(const scene &scene);
private:
    bool _initialized;
    SDL_Renderer *_renderer;
};

#endif
