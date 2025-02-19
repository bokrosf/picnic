#ifndef GAME_GAMECOORDINATOR_H
#define GAME_GAMECOORDINATOR_H

#include <engine/component/component.h>
#include <engine/component/initializable.h>
#include <game/game_ending.h>

class game_coordinator : public component, public initializable
{
public:
    ~game_coordinator() override;
    void initialize() override;
private:
    void end_game(const game_ending &ending);
};

#endif
