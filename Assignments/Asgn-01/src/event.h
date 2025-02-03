/********************************************************************************
* OOP345 – Assignment 01
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 02/02/2025 
********************************************************************************/
#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H
#include <string>
#include <chrono>
#include <iostream>
namespace seneca {
    class Event {
        std::string m_eventName{};
        std::chrono::nanoseconds m_duration{};
    public:
        Event();
        Event(const char* name, const std::chrono::nanoseconds& duration);
        friend std::ostream& operator<<(std::ostream& os, const Event& event);
    };
}
#endif