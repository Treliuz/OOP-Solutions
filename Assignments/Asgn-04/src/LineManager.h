/********************************************************************************
* OOP345 – Assignment 04
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 04/04/2025  
********************************************************************************/
#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H
#include "Workstation.h"
#include "CustomerOrder.h"
#include "Station.h"
#include <vector>
#include <iostream>
namespace seneca {
    class LineManager {
        std::vector<Workstation*> m_activeLine;
        size_t m_cntCustomerOrder{0};
        Workstation* m_firstStation;
    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };
}
#endif