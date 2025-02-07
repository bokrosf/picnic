#include <stdexcept>
#include <game/scene/scene_navigator.h>

std::stack<int> scene_navigator::detail::scenes;

namespace scene_navigator
{
    void pop()
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

    void reset_top()
    {
        scene_loader::queue([]() { scene_loader::active().reset(); });
    }
}
