/********************************************************************************
* OOP345 – Assignment 01
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 02/02/2025 
********************************************************************************/
#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include "event.h"
namespace seneca {
    class Logger {
        Event* col;
        size_t numEvents;
        size_t capacity;
    public:
        Logger();
        ~Logger();
        Logger(const Logger& src) = delete;
        Logger& operator=(Logger&) = delete;
        Logger(Logger&& src) noexcept;
        Logger& operator=(Logger&& src) noexcept;
        void addEvent(const Event& event);
        friend std::ostream& operator<<(std::ostream& os, const Logger& log);
    };
}
#endif