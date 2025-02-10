#ifndef ENGINE_RENDERING_TEXTURERENDERER_H
#define ENGINE_RENDERING_TEXTURERENDERER_H

#include <engine/rendering/renderer.h>

class texture_renderer : public renderer
{
public:
    void render(SDL_Renderer *renderer) override;
};

#endif
