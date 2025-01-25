#include "event.h"
#include "settings.h"
#include <iomanip>
namespace seneca {
    Event::Event() : m_eventName{""}, m_duration{0} {}

    Event::Event(const char* name, const std::chrono::nanoseconds& duration) : m_eventName(name), m_duration(duration) {}

    std::ostream& operator<<(std::ostream& os, const Event& event) {
        static size_t g_counter = 1;
        static size_t fieldWidth = 11;
        static double conversionRate = 1.0;

        if (g_settings.m_time_units == "microseconds") {
            fieldWidth = 8;
            conversionRate = 1e-3;
        } else if (g_settings.m_time_units == "milliseconds") {
            fieldWidth = 5;
            conversionRate = 1e-6;
        } else if (g_settings.m_time_units == "seconds") {
            fieldWidth = 2;
            conversionRate = 1e-9;
        }
        os << std::right << std::setw(2) << g_counter++ << ": " << std::setw(40) << event.m_eventName << " -> ";
        os << std::setw(fieldWidth) << event.m_duration.count() * conversionRate << " " << g_settings.m_time_units;

        return os;
    }
}
