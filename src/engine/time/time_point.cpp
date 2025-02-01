#include <engine/time/game_time.h>
#include <engine/time/time_point.h>

time_point::time_point()
    : time_point(0)
{
}

time_point::time_point(float seconds)
    : _seconds(seconds)
{
}

time_point::~time_point()
{
    unbind();
}

time_point &time_point::operator=(float seconds)
{
    _seconds = seconds;

    return *this;
}

time_point::operator float() const
{
    return _seconds;
}

time_point &time_point::operator+=(float duration)
{
    _seconds += duration;

    return *this;
}

void time_point::bind()
{
    if (!_context_id)
    {
        _context_id = game_time::bind(*this);
    }
}

void time_point::unbind()
{
    if (_context_id)
    {
        game_time::unbind(_context_id.value(), *this);
        _context_id.reset();
    }
}