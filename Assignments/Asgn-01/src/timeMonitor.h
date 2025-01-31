#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H
#include <chrono>
#include <string>
#include "event.h"
namespace seneca {
    class TimeMonitor {
        std::string eventName;
        std::chrono::high_resolution_clock::time_point start;
    public:
        void startEvent(const char* name);
        Event stopEvent();
    };
}
#endif