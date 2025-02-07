#ifndef ENGINE_LOGGING_LOGGER_H
#define ENGINE_LOGGING_LOGGER_H

#include <chrono>
#include <ostream>

namespace logger
{
    void destination(std::ostream &stream);

    template<typename... Args>
    void debug(Args &&...args);

    template<typename... Args>
    void information(Args &&...args);

    template<typename... Args>
    void warning(Args &&...args);

    template<typename... Args>
    void error(Args &&...args);

    namespace detail
    {
        extern std::ostream *destination;

        enum class log_level
        {
            debug,
            information,
            warning,
            error
        };

        std::string level_name(log_level level);

        template<typename... Args>
        void write(log_level level, Args &&...args);
    }

    template<typename... Args>
    void debug(Args &&...args)
    {
        using namespace detail;

        write(log_level::debug, args...);
    }

    template<typename... Args>
    void information(Args &&...args)
    {
        using namespace detail;

        write(log_level::information, args...);
    }

    template<typename... Args>
    void warning(Args &&...args)
    {
        using namespace detail;

        write(log_level::warning, args...);
    }

    template<typename... Args>
    void error(Args &&...args)
    {
        using namespace detail;

        write(log_level::error, args...);
    }

    template<typename... Args>
    void detail::write(detail::log_level level, Args &&...args)
    {
        if (!destination)
        {
            return;
        }

        *destination << std::format("{:%H:%M:%S}", std::chrono::system_clock::now());
        *destination << "|" << level_name(level) << "|";
        (*destination << ... << args) << std::endl;
    }
}

#endif
