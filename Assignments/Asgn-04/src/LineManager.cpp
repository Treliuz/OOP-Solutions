/********************************************************************************
* OOP345 – Assignment 04
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 06/04/2025  
********************************************************************************/
#include "LineManager.h"
#include "Utilities.h"
#include <fstream>
#include <algorithm>
namespace seneca {
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        try {
            std::string record;
            Utilities util;
            std::ifstream in(file);
            if (!in)
                throw std::runtime_error("Failed to open");
    
            std::vector<Workstation*> temp;
            temp.reserve(stations.size());
    
            while (std::getline(in, record)) {
                size_t next_pos = 0;
                bool more = true;
    
                std::string current = util.extractToken(record, next_pos, more);
                std::string next = more ? util.extractToken(record, next_pos, more) : "";
    
                auto currentSt = std::find_if(stations.begin(), stations.end(), 
                    [&](Workstation* work) {
                        return work->getItemName() == current;
                    });
    
                if (currentSt != stations.end() && 
                    std::find(temp.begin(), temp.end(), *currentSt) == temp.end()) {
                    temp.push_back(*currentSt);
                }
            }
    
            in.clear();
            in.seekg(0);
    
            while (std::getline(in, record)) {
                size_t next_pos = 0;
                bool more = true;
    
                std::string current = util.extractToken(record, next_pos, more);
                std::string next = more ? util.extractToken(record, next_pos, more) : "";
    
                auto currentSt = std::find_if(temp.begin(), temp.end(),
                    [&](Workstation* work) {
                        return work->getItemName() == current;
                    });
    
                auto nextSt = std::find_if(temp.begin(), temp.end(),
                    [&](Workstation* work) {
                        return work->getItemName() == next;
                    });
    
                if (currentSt != temp.end()) {
                    (*currentSt)->setNextStation(next.empty() ? nullptr : *nextSt);
                }
            }
    
            m_activeLine = std::move(temp);
    
            m_firstStation = *std::find_if(m_activeLine.begin(), m_activeLine.end(),
                [&](Workstation* first) {
                    return std::none_of(m_activeLine.begin(), m_activeLine.end(),
                        [&](Workstation* work) {
                            return work->getNextStation() == first;
                        });
                });
    
            m_cntCustomerOrder = g_pending.size();
        } catch (...) {
            throw "It broke";
        }
    }

    void LineManager::reorderStations() {
        std::vector<Workstation*> temp;
        temp.reserve(m_activeLine.size());

        Workstation* current = m_firstStation;

        while (current) {
            temp.push_back(current);
            current = current->getNextStation();
        }

        m_activeLine = std::move(temp);
    }

    bool LineManager::run(std::ostream& os) {
        static size_t count = 0;
        os << "Line Manager Iteration: " << ++count << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto& station : m_activeLine) {
            station->fill(os);
        }

        for (auto& station : m_activeLine) {
            station->attemptToMoveOrder();
        }

        bool complete = std::all_of(m_activeLine.begin(), m_activeLine.end(), [](const Workstation* station) {
            return station->isEmpty();
        });

        return complete && g_pending.empty() && g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }

    void LineManager::display(std::ostream& os) const {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](const Workstation* station) {
            station->display(os);
        });
    }
}