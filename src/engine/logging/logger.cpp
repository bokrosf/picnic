#include <engine/logging/logger.h>

namespace logger
{
    void destination(std::ostream &stream)
    {
        detail::destination = &stream;
    }
}

namespace logger::detail
{
    std::ostream *destination = nullptr;

    std::string level_name(log_level level)
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
}
