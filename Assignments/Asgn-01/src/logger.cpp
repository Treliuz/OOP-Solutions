/********************************************************************************
* OOP345 – Assignment 01
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 02/02/2025 
********************************************************************************/
#include "logger.h"
#include <utility>
namespace seneca {
    Logger::Logger() : col(nullptr), numEvents(0), capacity(0) {
    }

    Logger::Logger(Logger&& src) noexcept : col(src.col), numEvents(src.numEvents), capacity(src.numEvents) {
        src.col = nullptr;
        src.numEvents = 0;
        src.capacity = 0;
    }

    Logger& Logger::operator=(Logger&& src) noexcept {
        if (this != &src) {
            delete[] col;

            col = src.col;
            numEvents = src.numEvents;
            capacity = src.capacity;

            src.col = nullptr;
            src.numEvents = 0;
            src.capacity = 0;
        }
        return *this;
    }

    Logger::~Logger() {
        delete[] col;
    }

    void Logger::addEvent(const Event& event) {
        if (numEvents == capacity) {
            size_t tempCapacity = (capacity == 0) ? 1 : capacity * 2;
            Event* tempCol = new Event[tempCapacity];

            for (size_t i = 0; i < numEvents; i++) {
                tempCol[i] = col[i];
            }
            delete[] col;
            col = tempCol;
            capacity = tempCapacity;
        }
        col[numEvents++] = event;
    }

    std::ostream& operator<<(std::ostream& os, const Logger& logger) {
        for (size_t i = 0; i < logger.numEvents; i++) {
            os << logger.col[i] << std::endl;
        }
        return os;
    }
}