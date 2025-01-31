#include <engine/activatable.h>

activatable::activatable()
    : _active(true)
{
}

bool activatable::active() const
{
    return _active;
}

void activatable::active(bool active)
{
    _active = active;
}
