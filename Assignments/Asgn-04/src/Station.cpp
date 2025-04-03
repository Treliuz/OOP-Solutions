/********************************************************************************
* OOP345 – Assignment 04
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 03/04/2025  
********************************************************************************/
#include "Station.h"
#include <iostream>
#include <iomanip>

namespace seneca {
    size_t Station::m_widthField = 0;
    int Station::id_generator = 0;
    
    Station::Station(const std::string& record) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        m_name = util.extractToken(record, next_pos, more);
        m_serial = std::stoul(util.extractToken(record, next_pos, more)); 
        m_stock = std::stoul(util.extractToken(record, next_pos, more));

        if (m_widthField < util.getFieldWidth()) {
            m_widthField = util.getFieldWidth();
        }

        m_desc = util.extractToken(record, next_pos, more);
        m_id = ++id_generator;

        if (m_name.length() > m_widthField) {
            m_widthField = m_name.length();
        }
    }

    const std::string& Station::getItemName() const{
        return m_name;
    }

    size_t Station::getNextSerialNumber() {
        return m_serial++;
    }

    size_t Station::getQuantity() const {
        return m_stock;
    }

    void Station::updateQuantity() {
        m_stock > 0 ? m_stock-- : m_stock = 0;
    }

    void Station::display(std::ostream& os, bool full) const {
        os << std::right << std::setw(3) << std::setfill('0') << m_id << " | ";
        os << std::left << std::setw(m_widthField) << std::setfill(' ') << m_name << " | ";
        os << std::right << std::setw(6) << std::setfill('0') << m_serial << " | ";
        if (full) {
            os << std::setw(4) << std::setfill(' ') << m_stock << " | " << m_desc;
        }
        os << std::endl;
    }
}