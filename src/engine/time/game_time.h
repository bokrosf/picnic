#ifndef ENGINE_TIME_GAMETIME_H
#define ENGINE_TIME_GAMETIME_H

class time_point;

namespace game_time
{
    using context_id = int;

    void reset(context_id id);
    void erase(context_id id);
    void end_frame();
    float delta();
    float now();
    float real_now();
    context_id bind(time_point &time);
    void unbind(context_id id, time_point &bounded);
}

#endif
