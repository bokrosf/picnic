#include <game/scene/scene_navigator.h>
#include <game/scene/test_scene.h>
#include <game/picnic_app.h>

picnic_app::picnic_app(const app_configuration &configuration)
    : app(configuration)
{
}

void picnic_app::load_start_scene()
{
    scene_navigator::push<test_scene>();
}
