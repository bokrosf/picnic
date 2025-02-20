#ifndef GAME_PLAYER_BASKETPICKER_H
#define GAME_PLAYER_BASKETPICKER_H

#include <engine/component/component.h>
#include <engine/collision/collision_handler.h>

class basket_picker : public component, public collision_handler
{
public:
    basket_picker(unsigned int all_baskets);
    void collide(const collision &collision) override;
private:
    const unsigned int _all_baskets;
    unsigned int _picked_up;
};

#endif
