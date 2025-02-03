/********************************************************************************
* OOP345 – Assignment 01
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 02/02/2025 
********************************************************************************/
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