#include <SDL2/SDL.h>
#include <engine/assett.h>

#include <unordered_map>

namespace
{
    assett::id_type last_loaded_id;
    std::unordered_map<assett::id_type, SDL_Texture *> textures;
}

void assett::initialize()
{
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
