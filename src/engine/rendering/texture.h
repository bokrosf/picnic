#ifndef ENGINE_RENDERING_TEXTURE_H
#define ENGINE_RENDERING_TEXTURE_H

#include <glm/vec2.hpp>
#include <engine/assett.h>

struct texture
{
    assett::id_type id;
    glm::vec2 scale;
};

#endif
