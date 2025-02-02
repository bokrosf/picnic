#ifndef GAME_SCENE_TESTSCENE_H
#define GAME_SCENE_TESTSCENE_H

#include <engine/scene/scene.h>

class test_scene : public scene
{
public:
    test_scene(int id);
    void initialize() override;
};

#endif
