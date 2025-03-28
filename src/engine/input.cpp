#include <algorithm>
#include <vector>
#include <engine/input.h>

namespace
{
    std::vector<SDL_Event> events;
}

namespace input
{
    void read_events()
    {
        events.clear();
        SDL_Event current_event;

        while (SDL_PollEvent(&current_event))
        {
            events.push_back(current_event);
        }
    }

    bool key_down(SDL_Keycode key)
    {
        auto predicate = [key](const SDL_Event &event) { return event.type == SDL_EVENT_KEY_DOWN && event.key.key == key; };

        return std::any_of(events.begin(), events.end(), predicate);
    }

    bool occured(SDL_EventType event_type)
    {
        auto predicate = [event_type](const SDL_Event &event) { return event.type == event_type; };

        return std::any_of(events.begin(), events.end(), predicate);
    }
}
