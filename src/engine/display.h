#ifndef ENGINE_DISPLAY_H
#define ENGINE_DISPLAY_H

#include <string>
#include <SDL3/SDL.h>

namespace display
{
    void initialize(const std::string &window_title);
    void shutdown();
    SDL_Window &window();
    const SDL_DisplayMode &current_mode();
}

#endif
