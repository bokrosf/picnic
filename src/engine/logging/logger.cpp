#include <engine/logging/logger.h>

std::ostream *logger::detail::destination = nullptr;

void logger::destination(std::ostream &stream)
{
    detail::destination = &stream;
}

std::string logger::detail::level_name(log_level level)
{
    switch (level)
    {
        case log_level::debug:
            return "DEBUG";
        case log_level::information:
            return "INFO";
        case log_level::warning:
            return "WARNING";
        case log_level::error:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}
