#ifndef ENGINE_SUBSYSTEMINITIALIZATIONFAILED_H
#define ENGINE_SUBSYSTEMINITIALIZATIONFAILED_H

#include <stdexcept>

class subsystem_initialization_failed : public std::runtime_error
{
public:
    subsystem_initialization_failed(const std::string &what_arg);
    subsystem_initialization_failed(const char *what_arg);
    subsystem_initialization_failed(const std::runtime_error &other) noexcept;
};

#endif
