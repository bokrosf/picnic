#include <stdexcept>
#include <unordered_map>
#include <SDL3/SDL.h>
#include <engine/assett.h>
#include <engine/subsystem_initialization_failed.h>

namespace
{
    using namespace assett;

    SDL_Renderer *renderer = nullptr;
    id_type last_loaded_id;
    std::unordered_map<id_type, SDL_Texture *> textures;
}

namespace assett
{
    void initialize(SDL_Renderer &renderer)
    {
        if (::renderer)
        {
            throw std::logic_error("assett module already initialized.");
        }

        ::renderer = &renderer;
        last_loaded_id = 0;
    }

    void shutdown()
    {
        unload_all();
        renderer = nullptr;
    }

    std::optional<id_type> load(const std::string &file_path)
    {
        std::optional<id_type> id;
        SDL_Surface *surface = SDL_LoadBMP(file_path.c_str());

        if (!surface)
        {
            return id;
        }

        if (SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface))
        {
            textures[++last_loaded_id] = texture;
            id = last_loaded_id;
            SDL_DestroySurface(surface);
        }

        return id;
    }

    void unload_all()
    {
        for (auto [id, t] : textures)
        {
            SDL_DestroyTexture(t);
        }

        textures.clear();
    }

    SDL_Texture *texture(id_type id)
    {
        auto it = textures.find(id);

        return it != textures.end() ? it->second : nullptr;
    }
}
