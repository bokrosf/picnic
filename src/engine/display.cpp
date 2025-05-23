#include <sstream>
#include <stdexcept>
#include <engine/display.h>
#include <engine/subsystem_initialization_failed.h>

namespace
{
    bool initialized = false;
    SDL_DisplayID display_id = 0;
    SDL_Window *active_window = nullptr;

    const SDL_DisplayMode &display_mode(SDL_DisplayID id)
    {
        if (const SDL_DisplayMode *mode = SDL_GetCurrentDisplayMode(id))
        {
            return *mode;
        }

        std::stringstream error("Current display mode querying failed. ");
        error << "display_id: " << display_id << " " << SDL_GetError();

        throw std::runtime_error(error.str());
    }
}

namespace display
{
    void initialize(const std::string &window_title)
    {
        if (initialized)
        {
            throw std::logic_error("Display subsystem already initialized.");
        }

        int display_count = 0;
        SDL_DisplayID *displays = SDL_GetDisplays(&display_count);

        if (display_count > 0)
        {
            display_id = displays[0];
        }

        SDL_free(displays);

        if (display_count < 1)
        {
            throw subsystem_initialization_failed(std::string("No video display available.").append(SDL_GetError()));
        }

        active_window = SDL_CreateWindow(window_title.c_str(), 0, 0, SDL_WINDOW_FULLSCREEN);

        if (!active_window)
        {
            throw subsystem_initialization_failed(std::string("SDL Window creation failed. ").append(SDL_GetError()));
        }

        SDL_HideCursor();
        initialized = true;
    }

    void shutdown()
    {
        if (active_window)
        {
            SDL_DestroyWindow(active_window);
            active_window = nullptr;
        }

        initialized = false;
    }

    SDL_Window &window()
    {
        if (!initialized)
        {
            throw std::logic_error("Display subsystem must be initialized before querying the window.");
        }

        return *active_window;
    }

    const SDL_DisplayMode &current_mode()
    {
        if (!initialized)
        {
            throw std::logic_error("Display subsystem must be initialized before querying the current display mode.");
        }

        return display_mode(display_id);
    }
}
