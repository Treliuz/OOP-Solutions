#include "timeMonitor.h"
#include <iostream>

namespace seneca {
    void TimeMonitor::startEvent(const char* name) {
        eventName = name;
        start = std::chrono::high_resolution_clock::now();
    }

    Event TimeMonitor::stopEvent() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        return Event(eventName.c_str(), duration);
    }
}