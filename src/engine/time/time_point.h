#ifndef ENGINE_TIME_TIMEPOINT_H
#define ENGINE_TIME_TIMEPOINT_H

#include <optional>
#include <engine/time/game_time.h>

class time_point
{
public:
    time_point();
    explicit time_point(float seconds);
    ~time_point();
    time_point &operator=(float seconds);
    operator float() const;
    time_point &operator+=(float duration);
    void bind();
    void unbind();
private:
    float _seconds;
    std::optional<game_time::context_id> _context_id;

    friend void game_time::reset(game_time::context_id);
};

#endif