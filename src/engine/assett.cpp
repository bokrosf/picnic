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
