#include <map>
#include <vector>
#include <engine/display.h>
#include <engine/entity.h>
#include <engine/rendering/renderer.h>
#include <engine/rendering/rendering_engine.h>
#include <engine/subsystem_initialization_failed.h>

rendering_engine::rendering_engine()
    : _initialized(false)
    , _renderer(nullptr)
{
}

rendering_engine::~rendering_engine()
{
    shutdown();
}

void rendering_engine::initialize(SDL_Window &window)
{
    if (_initialized)
    {
        throw std::logic_error("Rendering engine already initialized.");
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(&window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        throw subsystem_initialization_failed(std::string("SDL Renderer creation failed. ").append(SDL_GetError()));
    }

    _renderer = renderer;
    _initialized = true;
}

void rendering_engine::shutdown()
{
    if (_renderer)
    {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
}

void rendering_engine::render(const scene &scene)
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

    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);

    for (const auto &[layer, renderers] : rendering_layers)
    {
        for (renderer *r : renderers)
        {
            r->render(_renderer);
        }
    }

    SDL_RenderPresent(_renderer);
}
