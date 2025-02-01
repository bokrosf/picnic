#ifndef ENGINE_SCENELOADER_H
#define ENGINE_SCENELOADER_H

#include <concepts>
#include <functional>
#include <unordered_map>
#include <utility>
#include <engine/scene/scene.h>

namespace scene_loader
{
    using operation = std::function<void()>;
    
    void initialize();
    void shutdown();

    template<typename Scene, typename... Args>
        requires std::derived_from<Scene, scene>
    int load(Args &&...args);

    void unload(int id);
    void activate(int id);
    scene &active();
    void queue(operation operation);
    void commit();

    namespace detail
    {
        extern int last_loaded_id;
        extern std::unordered_map<int, scene *> loaded_scenes;
    }
}

template<typename Scene, typename... Args>
    requires std::derived_from<Scene, scene>
int scene_loader::load(Args &&...args)
{
    using namespace detail;
    
    Scene *scene = nullptr;

    try
    {
        scene = new Scene(++last_loaded_id, std::forward<Args>(args)...);
        loaded_scenes[scene->id()] = scene;
    }
    catch (...)
    {
        delete scene;
        throw;
    }

    return scene->id();
}

#endif
