#ifndef GAME_PLAYER_PLAYERCONTROLLER_H
#define GAME_PLAYER_PLAYERCONTROLLER_H

#include <engine/component/behavior.h>
#include <engine/component/updatable.h>

class player_controller : public behavior, public updatable
{
public:
    player_controller();
    float speed;
    void update() override;
};

#endif
