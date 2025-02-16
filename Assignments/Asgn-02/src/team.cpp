/********************************************************************************
* OOP345 – Assignment 02
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 02/16/2025 
********************************************************************************/
#include "team.h"
namespace seneca {
    Team::Team() : m_teamName(""), m_members(nullptr), m_size(0) {}

    Team::Team(const char* name) : m_teamName(name), m_members(nullptr), m_size(0) {}

    Team::Team(const Team& other) : m_teamName(other.m_teamName), m_size(other.m_size) {
        m_members = new Character*[m_size];
        for (size_t i = 0; i < m_size; i++) {
            m_members[i] = other.m_members[i]->clone();
        }
    }

    Team::Team(Team&& other) noexcept : m_teamName(std::move(other.m_teamName)), m_members(other.m_members), m_size(other.m_size) {
        other.m_members = nullptr;
        other.m_size = 0;
    }

    Team& Team::operator=(const Team& other) {
        if (this != &other) {

            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i]; 
            }

            delete[] m_members;

            m_teamName = other.m_teamName;
            m_size = other.m_size;

            if (other.m_members != nullptr) {
                m_members = new Character*[m_size];
                for (size_t i = 0; i < m_size; ++i) {
                    m_members[i] = other.m_members[i]->clone();
                }
            } else {
                m_members = nullptr;
            }
        }
        return *this;
    }

    Team& Team::operator=(Team&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;
    
            m_teamName = std::move(other.m_teamName);
            m_members = other.m_members;
            m_size = other.m_size;
            
            other.m_members = nullptr;
            other.m_size = 0;
        }
        return *this;
    }
    
    Team::~Team() {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_members[i]; 
        }
        delete[] m_members; 
    }

    void Team::addMember(const Character* c) {
        if (c) {
            for (size_t i = 0; i < m_size; i++) {
                if (m_members[i]->getName() == c->getName()) {
                    return;
                }
            }
        }
        
        Character** temp = new Character*[m_size + 1];

        for (size_t i = 0; i < m_size; i++) {
            temp[i] = m_members[i];
        }

        temp[m_size] = c->clone();
        delete[] m_members;
        m_members = temp;
        m_size++;
    }

    void Team::removeMember(const std::string& c) {
        for (size_t i = 0; i < m_size; i++) {
            if (m_members[i]->getName() == c) {
                delete m_members[i];

                for (size_t j = i; j < m_size - 1; j++) {
                    m_members[j] = m_members[j + 1];
                }
                m_size--;

                Character** temp = new Character*[m_size];
                for (size_t i = 0; i < m_size; i++) {
                    temp[i] = m_members[i];
                }

                delete[] m_members;
                m_members = temp;
                return;
            }
        }
    }

    Character* Team::operator[](size_t idx) const {
        if (idx >= m_size) {
            std::cerr << idx << " is out of bounds!" << std::endl;
            return nullptr;
        }
        return m_members[idx];
    }

    void Team::showMembers() const {
        if (m_size == 0) {
            std::cout << "No team." << std::endl;
            return;
        }

        std::cout << "[Team] " << m_teamName << std::endl;

        for (size_t i = 0; i < m_size; i++) {
            std::cout << "    " << (i + 1) << ": "<< *m_members[i] << std::endl;
        }
    }
}