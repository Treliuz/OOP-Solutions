/********************************************************************************
* OOP345 – Assignment 01
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 02/02/2025 
********************************************************************************/
#include "event.h"
#include "settings.h"
#include <iomanip>
namespace seneca {
    Event::Event() {}
     
    Event::Event(const char* name, const std::chrono::nanoseconds& duration) : m_eventName(name), m_duration(duration) {}

    std::ostream& operator<<(std::ostream& os, const Event& event) {
        static size_t g_counter = 1;
        static size_t fieldWidth;

        os << std::right << std::setw(2) << g_counter++ << ": " << std::setw(40) << event.m_eventName << " -> ";
        if (g_settings.m_time_units == "microseconds") {
            fieldWidth = 8;
            os << std::setw(fieldWidth) << std::chrono::duration_cast<std::chrono::microseconds>(event.m_duration).count() << " " << g_settings.m_time_units;
        }
        else if (g_settings.m_time_units == "milliseconds") {
            fieldWidth = 5;
            os << std::setw(fieldWidth) << std::chrono::duration_cast<std::chrono::milliseconds>(event.m_duration).count() << " " << g_settings.m_time_units;
        }
        else if (g_settings.m_time_units == "seconds") {
            fieldWidth = 2;
            os << std::setw(fieldWidth) << std::chrono::duration_cast<std::chrono::seconds>(event.m_duration).count() << " " << g_settings.m_time_units;
        }
        else {
            fieldWidth = 11;
            os << std::setw(fieldWidth) << event.m_duration.count() << " nanoseconds";
        }

        return os;
    }
}
