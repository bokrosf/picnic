#include <stdexcept>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <engine/assett.h>

namespace
{
    SDL_Renderer *renderer;
    assett::id_type last_loaded_id;
    std::unordered_map<assett::id_type, SDL_Texture *> textures;
}

void assett::initialize(SDL_Renderer &renderer)
{
    if (::renderer)
    {
        throw std::logic_error("assett module already initialized.");
    }

    ::renderer = &renderer;
    last_loaded_id = -1;
}

void assett::shutdown()
{
    unload_all();
}

void assett::unload_all()
{
    for (auto [id, t] : textures)
    {
        SDL_DestroyTexture(t);
    }

    textures.clear();
}

SDL_Texture *assett::texture(id_type id)
{
    auto it = textures.find(id);

    return it != textures.end() ? it->second : nullptr;
}
