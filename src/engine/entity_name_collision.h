#ifndef ENGINE_ENTITYNAMECOLLISION_H
#define ENGINE_ENTITYNAMECOLLISION_H

#include <stdexcept>
#include <string>

class entity_name_collision : public std::logic_error
{
public:
    entity_name_collision(const std::string &what_arg);
    entity_name_collision(const char *what_arg);
    entity_name_collision(const std::logic_error &other) noexcept;
};

#endif
