#include <stdexcept>
#include <game/scene/scene_navigator.h>

std::stack<int> scene_navigator::detail::scenes;

void scene_navigator::pop()
{
    using namespace detail;

    scene_loader::queue([]()
    {
        if (scenes.empty())
        {
            return;
        }

        scene_loader::unload(scenes.top());
        scenes.pop();
        scene_loader::activate(scenes.top());
    });
}

void scene_navigator::reset_top()
{
    scene_loader::queue([]() { scene_loader::active().reset(); });
}
