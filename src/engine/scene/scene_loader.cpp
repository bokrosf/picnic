#include <stdexcept>
#include <string>
#include <queue>
#include <engine/messaging/messenger.h>
#include <engine/scene/scene_destroyed.h>
#include <engine/scene/scene_loader.h>

namespace
{
    const int default_loaded_id = -1;
    scene *active_scene = nullptr;
    std::queue<scene_loader::operation> operations;
}

namespace scene_loader
{
    using namespace detail;

    void initialize()
    {
        last_loaded_id = default_loaded_id;
        active_scene = nullptr;
    }

    void shutdown()
    {
        unload_all();
    }

    void unload(int id)
    {
        if (!loaded_scenes.contains(id))
        {
            throw std::invalid_argument(std::string("No scene loaded with the given id. id: ").append(std::to_string(id)));
        }

        auto node = loaded_scenes.extract(id);

        if (node.mapped() == active_scene)
        {
            active_scene = nullptr;
        }

        delete node.mapped();
        messenger::send(scene_destroyed{id});
    }

    void unload_all()
    {
        for (auto [id, scene] : loaded_scenes)
        {
            delete scene;
            messenger::send(scene_destroyed{id});
        }

        loaded_scenes.clear();
        active_scene = nullptr;
    }

    void activate(int id)
    {
        if (!loaded_scenes.contains(id))
        {
            throw std::invalid_argument(std::string("No scene loaded with the given id. id: ").append(std::to_string(id)));
        }

        active_scene = loaded_scenes[id];
    }

    scene &active()
    {
        if (!active_scene)
        {
            throw std::runtime_error("There is no active scene.");
        }

        return *active_scene;
    }

    void queue(operation operation)
    {
        operations.push(operation);
    }

    void commit()
    {
        while (!operations.empty())
        {
            operations.front()();
            operations.pop();
        }
    }
}

namespace scene_loader::detail
{
    int last_loaded_id = default_loaded_id;
    std::unordered_map<int, scene *> loaded_scenes;
}
