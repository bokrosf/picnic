#ifndef ENGINE_ASSETT_H
#define ENGINE_ASSETT_H

#include <optional>
#include <string>
#include <SDL3/SDL.h>

namespace assett
{
    using id_type = unsigned int;

    void initialize(SDL_Renderer &renderer);
    void shutdown();
    std::optional<id_type> load(const std::string &file_path);
    void unload_all();
    SDL_Texture *texture(id_type id);
}

#endif
