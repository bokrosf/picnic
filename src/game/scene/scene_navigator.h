#ifndef GAME_SCENE_SCENENAVIGATOR_H
#define GAME_SCENE_SCENENAVIGATOR_H

#include <concepts>
#include <stack>
#include <utility>
#include <engine/scene/scene.h>
#include <engine/scene/scene_loader.h>

namespace scene_navigator
{
    template<typename Scene, typename... Args>
        requires std::derived_from<Scene, scene>
    void push(Args &&...args);

    void pop();
    void reset_top();

    template<typename Scene, typename... Args>
        requires std::derived_from<Scene, scene>
    void reset_root(Args &&...args);

    namespace detail
    {
        extern std::stack<int> scenes;
    }

    template<typename Scene, typename... Args>
        requires std::derived_from<Scene, scene>
    void push(Args &&...args)
    {
        using namespace detail;

        scene_loader::queue([args...]()
        {
            int scene_id = scene_loader::load<Scene>(args...);
            scenes.push(scene_id);
            scene_loader::activate(scene_id);
            scene_loader::active().initialize();
        });
    }

    template<typename Scene, typename... Args>
        requires std::derived_from<Scene, scene>
    void reset_root(Args &&...args)
    {
        using namespace detail;

        scene_loader::queue([args...]()
        {
            scene_loader::unload_all();

            while (!scenes.empty())
            {
                scenes.pop();
            }

            push<Scene>(std::forward<Args>(args)...);
        });
    }
}

#endif
