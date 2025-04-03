/********************************************************************************
* OOP345 – Assignment 04
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 03/04/2025  
********************************************************************************/
#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include "Utilities.h"
#include <string>
namespace seneca {
    class Station {
        int m_id{};
        std::string m_name {};
        std::string m_desc {};
        size_t m_serial {};
        size_t m_stock {};
        static size_t m_widthField;
        static int id_generator;
    public:
        Station(const std::string& str);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}
#endif