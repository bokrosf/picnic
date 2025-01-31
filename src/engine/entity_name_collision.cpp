#include <engine/entity_name_collision.h>

entity_name_collision::entity_name_collision(const std::string &what_arg)
    : std::logic_error(what_arg)
{
}

entity_name_collision::entity_name_collision(const char *what_arg)
    : std::logic_error(what_arg)
{
}

entity_name_collision::entity_name_collision(const std::logic_error &other) noexcept
    : std::logic_error(other)
{
}
