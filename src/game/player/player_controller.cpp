#include <engine/component/transform.h>
#include <engine/time/game_time.h>
#include <engine/input.h>
#include <game/player/player_controller.h>

player_controller::player_controller()
    : speed(0)
{
}

void player_controller::update()
{
    glm::vec2 direction(0);
    
    if (input::key_down(SDLK_UP) || input::key_down(SDLK_W))
    {
        direction = glm::vec2(0, -1);
    }
    else if (input::key_down(SDLK_DOWN) || input::key_down(SDLK_S))
    {
        direction = glm::vec2(0, 1);
    }
    else if (input::key_down(SDLK_LEFT) || input::key_down(SDLK_A))
    {
        direction = glm::vec2(-1, 0);
    }
    else if (input::key_down(SDLK_RIGHT) || input::key_down(SDLK_D))
    {
        direction = glm::vec2(1, 0);
    }

    transform().translate(game_time::delta() * speed * direction);
}
