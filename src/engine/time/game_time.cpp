#include <unordered_map>
#include <utility>
#include <vector>
#include <SDL3/SDL.h>
#include <engine/time/game_time.h>
#include <engine/time/time_point.h>

namespace
{
    using namespace game_time;

    const float precision = 0.001F;

    struct context
    {
        context(context_id, Uint64 started_at);

        const context_id id;
        Uint64 switched_away;
        Uint64 frame_started_at;
        float delta;
        std::vector<time_point *> bound_times;
    };

    std::unordered_map<context_id, context> contexts;
    context *current = nullptr;

    context::context(context_id id, Uint64 started_at)
        : id(id)
        , switched_away(0)
        , frame_started_at(started_at)
        , delta(0)
    {
    }
}

namespace game_time
{
    void reset(context_id id)
    {
        Uint64 now = SDL_GetTicks();

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

    void erase(context_id id)
    {
        if (current && current->id == id)
        {
            current = nullptr;
        }

        contexts.erase(id);
    }

    void end_frame()
    {
        Uint64 now = SDL_GetTicks();
        current->delta = precision * (now - current->frame_started_at);
        current->frame_started_at = now;
    }

    float delta()
    {
        return current->delta;
    }

    float now()
    {
        return precision * current->frame_started_at;
    }

    float real_now()
    {
        return precision * SDL_GetTicks();
    }

    context_id bind(time_point &time)
    {
        current->bound_times.emplace_back(&time);

        return current->id;
    }

    void unbind(context_id id, time_point &bounded)
    {
        std::erase(contexts.at(id).bound_times, &bounded);
    }
}
