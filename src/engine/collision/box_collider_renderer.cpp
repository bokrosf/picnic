#include <engine/collision/box_collider_renderer.h>
#include <engine/entity.h>

void box_collider_renderer::initialize()
{
    _collider = &attached_to().attached_component<box_collider>();
}

void box_collider_renderer::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 243, 255);
    
    glm::vec2 begin = _collider->transform().position() + _collider->area();
    glm::vec2 end = _collider->transform().position() + glm::vec2(-_collider->area().x, _collider->area().y);
    SDL_RenderLine(renderer, begin.x, begin.y, end.x, end.y);

    begin = end;
    end = _collider->transform().position() + glm::vec2(-_collider->area().x, -_collider->area().y);
    SDL_RenderLine(renderer, begin.x, begin.y, end.x, end.y);
    
    begin = end;
    end = _collider->transform().position() + glm::vec2(_collider->area().x, -_collider->area().y);
    SDL_RenderLine(renderer, begin.x, begin.y, end.x, end.y);
    
    begin = end;
    end = _collider->transform().position() + glm::vec2(_collider->area().x, _collider->area().y);
    SDL_RenderLine(renderer, begin.x, begin.y, end.x, end.y);

    begin = _collider->transform().position();
    end = _collider->transform().position() + _collider->area();
    SDL_RenderLine(renderer, begin.x, begin.y, end.x, end.y);
}
