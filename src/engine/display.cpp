#include <sstream>
#include <stdexcept>
#include <SDL2/SDL_mouse.h>
#include <engine/display.h>
#include <engine/subsystem_initialization_failed.h>

namespace
{
    bool initialized = false;
    const int display_id = 0;
    SDL_Window *active_window = nullptr;

    SDL_DisplayMode current_mode()
    {        
        SDL_DisplayMode display_mode;

        if (SDL_GetCurrentDisplayMode(display_id, &display_mode) != 0)
        {
            std::stringstream error("Current display mode querying failed. ");
            error << "display_id: " << display_id << " " << SDL_GetError();
            
            throw std::runtime_error(error.str());
        }

        return display_mode;
    }
}

void display::initialize(const std::string &window_title)
{
    if (initialized)
    {
        throw std::logic_error("Display subsystem already initialized.");
    }
    
    if (int display_count = SDL_GetNumVideoDisplays(); display_count < 1)
    {
        throw subsystem_initialization_failed(std::string("No video display available.").append(SDL_GetError()));
    }
   
    SDL_DisplayMode display_mode = ::current_mode();
    active_window = SDL_CreateWindow(
        window_title.c_str(),
        0,
        0,
        display_mode.w,
        display_mode.h,
        SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!active_window)
    {
        throw subsystem_initialization_failed(std::string("SDL Window creation failed. ").append(SDL_GetError()));
    }

    SDL_ShowCursor(SDL_DISABLE);
    initialized = true;
}

void display::shutdown()
{
    if (active_window)
    {
        SDL_DestroyWindow(active_window);
        active_window = nullptr;
    }

    initialized = false;
}

SDL_Window &display::window()
{
    if (!initialized)
    {
        throw std::logic_error("Display subsystem must be initialized before querying the window.");
    }

    return *active_window;
}

SDL_DisplayMode display::current_mode()
{
    if (!initialized)
    {
        throw std::logic_error("Display subsystem must be initialized before querying the current display mode.");
    }
    
    return ::current_mode();
}
