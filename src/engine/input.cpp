#include <algorithm>
#include <vector>
#include <engine/input.h>

namespace
{
    std::vector<SDL_Event> events;
}

void input::read_events()
{
    events.clear();
    SDL_Event current_event;

    while (SDL_PollEvent(&current_event))
    {
        events.push_back(current_event);
    }
}

bool input::key_down(SDL_KeyCode key)
{
    auto predicate = [key](const SDL_Event &event) { return event.type == SDL_KEYDOWN && event.key.keysym.sym == key; };

    return std::any_of(events.begin(), events.end(), predicate);
}

bool input::occured(SDL_EventType event_type)
{
    auto predicate = [event_type](const SDL_Event &event) { return event.type == event_type; };

    return std::any_of(events.begin(), events.end(), predicate);
}
