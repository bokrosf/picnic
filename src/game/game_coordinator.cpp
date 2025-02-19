#include <engine/messaging/messenger.h>
#include <game/game_coordinator.h>
#include <game/scene/game_ending_scene.h>
#include <game/scene/scene_navigator.h>

game_coordinator::~game_coordinator()
{
    messenger::unsubscribe<game_ending>(this);
}

void game_coordinator::initialize()
{
    messenger::subscribe(this, &game_coordinator::end_game);
}

void game_coordinator::end_game(const game_ending &ending)
{
    messenger::unsubscribe<game_ending>(this);
    scene_navigator::push<game_ending_scene>(ending);
}
