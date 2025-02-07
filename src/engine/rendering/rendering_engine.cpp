#include <map>
#include <vector>
#include <engine/display.h>
#include <engine/entity.h>
#include <engine/rendering/renderer.h>
#include <engine/rendering/rendering_engine.h>
#include <engine/subsystem_initialization_failed.h>

namespace
{
    SDL_Renderer *native_renderer = nullptr;
}

namespace rendering_engine
{
    void initialize(SDL_Window &window)
    {
        if (native_renderer)
        {
            throw std::logic_error("Rendering engine already initialized.");
        }

        native_renderer = SDL_CreateRenderer(&window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (!native_renderer)
        {
            throw subsystem_initialization_failed(std::string("SDL Renderer creation failed. ").append(SDL_GetError()));
        }
    }

    void shutdown()
    {
        if (native_renderer)
        {
            SDL_DestroyRenderer(native_renderer);
            native_renderer = nullptr;
        }
    }

    void render(const scene &scene)
    {
        std::map<int, std::vector<renderer *>> rendering_layers;
        auto entity_filter = [](const entity *e) { return e->active() && e->life_state() == life_state::alive; };

        for (const entity &entity : scene.traverse(entity_filter))
        {
            auto filter_renderer = [](const renderer *r) { return r->active() && r->life_state() == life_state::alive; };

            for (renderer *r : entity.all_attached_components<renderer>() | std::views::filter(filter_renderer))
            {
                rendering_layers[r->layer_order].push_back(r);
            }
        }

        SDL_SetRenderDrawColor(native_renderer, 0, 0, 0, 255);
        SDL_RenderClear(native_renderer);

        for (const auto &[layer, renderers] : rendering_layers)
        {
            for (renderer *r : renderers)
            {
                r->render(native_renderer);
            }
        }

        SDL_RenderPresent(native_renderer);
    }
}
