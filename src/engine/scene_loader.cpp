#include <stdexcept>
#include <string>
#include <engine/messaging/messenger.h>
#include <engine/scene_destroyed.h>
#include <engine/scene_loader.h>

scene_loader::scene_loader()
    : _last_loaded_id(-1)
    , _active_scene(nullptr)
{
}

scene_loader::~scene_loader()
{
    unload_all();
}

void scene_loader::unload(int id)
{
    if (!_loaded_scenes.contains(id))
    {
        throw std::invalid_argument(std::string("No scene loaded with the given id. id: ").append(std::to_string(id)));
    }

    auto node = _loaded_scenes.extract(id);
    
    if (node.mapped() == _active_scene)
    {
        _active_scene = nullptr;
    }
    
    delete node.mapped();
    messenger::send(scene_destroyed{id});
}

void scene_loader::unload_all()
{
    for (auto [id, scene] : _loaded_scenes)
    {
        delete scene;
        messenger::send(scene_destroyed{id});
    }
    
    _loaded_scenes.clear();
    _active_scene = nullptr;
}

void scene_loader::activate(int id)
{
    if (!_loaded_scenes.contains(id))
    {
        throw std::invalid_argument(std::string("No scene loaded with the given id. id: ").append(std::to_string(id)));
    }

    _active_scene = _loaded_scenes[id];
}

scene &scene_loader::active() const
{
    if (!_active_scene)
    {
        throw std::runtime_error("There is no active scene.");
    }

    return *_active_scene;
}

void scene_loader::queue(operation operation)
{
    _operations.push(operation);
}

void scene_loader::commit()
{
    while (!_operations.empty())
    {
        _operations.front()(*this);
        _operations.pop();
    }
}
