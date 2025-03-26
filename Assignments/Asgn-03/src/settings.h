/********************************************************************************
* OOP345 – Assignment 03
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 21/03/2025 
********************************************************************************/
#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H
namespace seneca {
    struct Settings {
        unsigned short m_maxSummaryWidth = 80;
        bool m_tableView = false;
    };
    extern Settings g_settings;
}
#endif