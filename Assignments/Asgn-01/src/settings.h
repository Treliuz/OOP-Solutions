/********************************************************************************
* OOP345 – Assignment 01
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 02/02/2025 
********************************************************************************/
#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H
#include <string>
namespace seneca {
    struct Settings {
        bool m_show_all{false};
        bool m_verbose{false};
        std::string m_time_units = "nanoseconds";
    };
    extern Settings g_settings;
}
#endif 