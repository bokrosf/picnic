#include <stdexcept>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <engine/assett.h>
#include <engine/subsystem_initialization_failed.h>

namespace
{
    SDL_Renderer *renderer = nullptr;
    assett::id_type last_loaded_id;
    std::unordered_map<assett::id_type, SDL_Texture *> textures;
}

namespace assett
{
    void initialize(SDL_Renderer &renderer)
    {
        if (::renderer)
        {
            throw std::logic_error("assett module already initialized.");
        }

        int image_types = IMG_INIT_PNG | IMG_INIT_JPG;
        int initialized_types = IMG_Init(image_types);

        if (initialized_types != image_types)
        {
            throw subsystem_initialization_failed(
                std::string("SDL Image initilaization failed. requested: ")
                    .append(std::to_string((image_types)))
                    .append("initialized: ")
                    .append(std::to_string(initialized_types)));
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

        if (SDL_Texture *texture = IMG_LoadTexture(renderer, file_path.c_str()))
        {
            textures[++last_loaded_id] = texture;
            id = last_loaded_id;
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
