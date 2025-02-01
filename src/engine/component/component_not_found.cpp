#include <engine/component/component_not_found.h>

component_not_found::component_not_found(const std::string &what_arg)
    : logic_error(what_arg)
{
}

component_not_found::component_not_found(const char *what_arg)
    : logic_error(what_arg)
{
}

component_not_found::component_not_found(const std::logic_error &other) noexcept
    : logic_error(other)
{
}
