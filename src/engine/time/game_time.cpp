#include <unordered_map>
#include <utility>
#include <vector>
#include <SDL2/SDL.h>
#include <engine/time/game_time.h>
#include <engine/time/time_point.h>

namespace
{
    const float precision = 0.001F;

    struct context
    {
        context(game_time::context_id, Uint64 started_at);

        const game_time::context_id id;
        Uint64 switched_away;
        Uint64 frame_started_at;
        float delta;
        std::vector<time_point *> bound_times;
    };

    std::unordered_map<game_time::context_id, context> contexts;
    context *current = nullptr;
}

::context::context(game_time::context_id id, Uint64 started_at)
    : id(id)
    , switched_away(0)
    , frame_started_at(started_at)
    , delta(0)
{
}

void game_time::reset(game_time::context_id id)
{
    Uint64 now = SDL_GetTicks64();

    if (current)
    {
        current->switched_away = now;
    }

    current = &contexts.try_emplace(id, id, now).first->second;
    current->frame_started_at = now;
    current->delta = 0;
    float switch_duration = precision * (now - current->switched_away);

    for (auto *bounded : current->bound_times)
    {
        bounded->_seconds += switch_duration;
    }
}

void game_time::erase(context_id id)
{
    if (current && current->id == id)
    {
        current = nullptr;
    }

    contexts.erase(id);
}

void game_time::end_frame()
{
    Uint64 now = SDL_GetTicks64();
    current->delta = precision * (now - current->frame_started_at);
    current->frame_started_at = now;
}

float game_time::delta()
{
    return current->delta;
}

float game_time::now()
{
    return precision * current->frame_started_at;
}

float game_time::real_now()
{
    return precision * SDL_GetTicks64();
}

game_time::context_id game_time::bind(time_point &time)
{
    current->bound_times.emplace_back(&time);

    return current->id;
}

void game_time::unbind(context_id id, time_point &bounded)
{
    std::erase(contexts.at(id).bound_times, &bounded);
}