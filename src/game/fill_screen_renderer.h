#ifndef GAME_FILLSCREENRENDERER_H
#define GAME_FILLSCREENRENDERER_H

#include <engine/rendering/renderer.h>

class fill_screen_renderer : public renderer
{
public:
    void render(SDL_Renderer *renderer) override;
};

#endif
