#ifndef ENGINE_RENDERING_IMAGERENDERER_H
#define ENGINE_RENDERING_IMAGERENDERER_H

#include <engine/rendering/renderer.h>

class image_renderer : public renderer
{
public:
    image_renderer();
    ~image_renderer() override;
    void render(SDL_Renderer *renderer) override;
private:
    void load_texture(SDL_Renderer *renderer);
    void unload_texture();

    SDL_Texture *_texture;
    SDL_Rect _texture_region;
    SDL_FRect _draw_region;
};

#endif
