#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include "event.h"
namespace seneca {
    class Logger {
        Event* col;
        size_t numEvents{};
        size_t capacity{};
    public:
        Logger();
        ~Logger();
        Logger(const Logger& src) = delete;
        Logger& operator=(Logger&) = delete;
        Logger(Logger&& src);
        Logger& operator=(Logger&& src) noexcept;
        void addEvent(const Event& event);
        friend std::ostream& operator<<(std::ostream& os, const Logger& log);
    };
}
#endif