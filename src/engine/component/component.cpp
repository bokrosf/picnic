#include <engine/component_destroyed.h>
#include <engine/component/component.h>
#include <engine/entity.h>
#include <engine/messaging/messenger.h>

component::component()
    : _life_state(life_state::initializing)
{
}

void component::destroy()
{
    if (_life_state == life_state::destroyed)
    {
        return;
    }

    _life_state = life_state::destroyed;
    detach();
    messenger::send(component_destroyed{*this});
}

life_state component::life_state() const
{
    return _life_state;
}

entity &component::attached_to() const
{
    return *_attached_to;
}

const transform &component::transform() const
{
    return attached_to().transform();
}

transform &component::transform()
{
    return attached_to().transform();
}

void component::detach()
{
}
