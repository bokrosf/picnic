#ifndef GAME_SCENE_GAMEENDINGSCENE_H
#define GAME_SCENE_GAMEENDINGSCENE_H

#include <engine/scene/scene.h>
#include <game/game_ending.h>

class game_ending_scene : public scene
{
public:
    game_ending_scene(scene::id_type id, game_ending ending);
    void initialize() override;
private:
    const game_ending _ending;
};

#endif
