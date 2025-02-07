#include <stdexcept>
#include <game/scene/scene_navigator.h>

namespace scene_navigator
{
    using namespace detail;

    void pop()
    {
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

namespace scene_navigator::detail
{
    std::stack<int> scenes;
}
