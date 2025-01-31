#ifndef ENGINE_SCENELOADER_H
#define ENGINE_SCENELOADER_H

#include <concepts>
#include <functional>
#include <queue>
#include <unordered_map>
#include <utility>
#include <engine/scene.h>

class scene_loader final
{
public:
    using operation = std::function<void(scene_loader &)>;

    scene_loader();
    ~scene_loader();    

    template<typename Scene, typename... Args>
        requires std::derived_from<Scene, scene>
    int load(Args &&...args);

    void unload(int id);
    void unload_all();
    void activate(int id);
    scene &active() const;
    void queue(operation operation);
    void commit();
private:
    int _last_loaded_id;
    std::unordered_map<int, scene *> _loaded_scenes;
    scene *_active_scene;
    std::queue<operation> _operations;
};

template<typename Scene, typename... Args>
    requires std::derived_from<Scene, scene>
int scene_loader::load(Args &&...args)
{
    Scene *scene = nullptr;

    try
    {
        scene = new Scene(++_last_loaded_id, std::forward<Args>(args)...);
        _loaded_scenes[scene->id()] = scene;
    }
    catch (...)
    {
        delete scene;
        throw;
    }

    return scene->id();
}

#endif
