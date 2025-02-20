#include <engine/entity.h>
#include <engine/messaging/messenger.h>
#include <game/game_ending.h>
#include <game/player/basket_picker.h>
#include <game/tag.h>

basket_picker::basket_picker(unsigned int all_baskets)
    : _all_baskets(all_baskets)
    , _picked_up(0)
{
}

void basket_picker::collide(const collision &collision)
{
    if (collision.collider.attached_to().tag() != tag::basket)
    {
        return;
    }

    collision.collider.attached_to().destroy();
    ++_picked_up;

    if (_picked_up == _all_baskets)
    {
        messenger::send(game_ending::baskets_collected);
    }
}
