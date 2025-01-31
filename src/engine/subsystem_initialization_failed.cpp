#include <engine/subsystem_initialization_failed.h>

subsystem_initialization_failed::subsystem_initialization_failed(const std::string &what_arg)
    : runtime_error(what_arg)
{
}

subsystem_initialization_failed::subsystem_initialization_failed(const char *what_arg)
    : runtime_error(what_arg)
{
}

subsystem_initialization_failed::subsystem_initialization_failed(const std::runtime_error &other) noexcept
    : runtime_error(other)
{
}
