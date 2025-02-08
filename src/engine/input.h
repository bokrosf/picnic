#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include <SDL3/SDL.h>

namespace input
{
    void read_events();
    bool key_down(SDL_Keycode key);
    bool occured(SDL_EventType event_type);
}

#endif
