#include <engine/assett.h>
#include <engine/entity.h>
#include <engine/rendering/texture_renderer.h>
#include <game/assett.h>
#include <game/scene/test_scene.h>

namespace
{
    void load_assetts();
}

test_scene::test_scene(int id)
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
        if (auto id = assett::load(game::assett::texture::test))
        {
            entity &a = entity::create();
            texture tex{.id = *id, .scale = 5.0F * glm::vec2(1.0, 1.0)};
            material m{.texture = tex};
            a.add_component<texture_renderer>().material(m);
            a.transform().position(0.5F * glm::vec2(1920, 1080));
        }
    }
}
