#include <engine/assett.h>
#include <engine/collision/box_collider.h>
#include <engine/collision/box_collider_renderer.h>
#include <engine/entity.h>
#include <engine/rendering/texture_renderer.h>
#include <game/assett.h>
#include <game/game_coordinator.h>
#include <game/player/basket_picker.h>
#include <game/player/player_controller.h>
#include <game/scene/test_scene.h>
#include <game/tag.h>

namespace
{
    void load_assetts();
}

test_scene::test_scene(scene::id_type id)
    : scene(id)
{
}

test_scene::~test_scene()
{
    assett::unload_all();
}

void test_scene::initialize()
{
    load_assetts();
}

namespace
{
    void load_assetts()
    {
        entity &coordinator = entity::create();
        coordinator.add_component<game_coordinator>();

        auto assett_id = assett::load(game::assett::texture::bear);
        entity &player = entity::create();
        texture tex{.id = *assett_id, .scale = glm::vec2(5.0F)};
        player.add_component<texture_renderer>().material(material{.texture = tex});
        player.transform().position(0.5F * glm::vec2(1920, 1080));
        player.add_component<player_controller>().speed = 1920;
        player.add_component<box_collider>(glm::vec2(25, 25));
        player.add_component<box_collider_renderer>();
        const unsigned int all_baskets = 4;
        player.add_component<basket_picker>(all_baskets);

        for (unsigned int i = 1; i <= all_baskets; ++i)
        {
            entity &basket = entity::create();
            basket.tag(tag::basket);
            basket.add_component<texture_renderer>().material(material{.texture = tex});
            basket.transform().position(0.5F * glm::vec2(1920, 1080) + glm::vec2(i * 100, 0));
            basket.add_component<box_collider>(glm::vec2(25, 25));
            basket.add_component<box_collider_renderer>();
        }
    }
}
