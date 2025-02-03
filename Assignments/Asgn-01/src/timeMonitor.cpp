/********************************************************************************
* OOP345 – Assignment 01
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 02/02/2025 
********************************************************************************/
#include "timeMonitor.h"
#include "settings.h"
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