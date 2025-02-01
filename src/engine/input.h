#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include <SDL2/SDL.h>

namespace input
{
    void read_events();
    bool key_down(SDL_KeyCode key);
    bool occured(SDL_EventType event_type);
}

#endif
