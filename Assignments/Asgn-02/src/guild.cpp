/********************************************************************************
* OOP345 – Assignment 02
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 02/16/2025 
********************************************************************************/
#include "guild.h"
namespace seneca {
    Guild::Guild() : m_guildName(""), m_members(nullptr), m_size(0) {}

    Guild::Guild(const char* name) : m_guildName(name), m_members(nullptr), m_size(0) {}

    Guild::Guild(const Guild& other) : m_guildName(other.m_guildName), m_size(other.m_size) {
        m_members = new Character*[m_size];
        for (size_t i = 0; i < m_size; i++) {
            m_members[i] = other.m_members[i]->clone();
        }
    }

    Guild::Guild(Guild&& other) noexcept : m_guildName(std::move(other.m_guildName)), m_members(other.m_members), m_size(other.m_size) {
        other.m_members = nullptr;
        other.m_size = 0;
    }

    Guild& Guild::operator=(const Guild& other) {
        if (this != &other) {
            
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }

            delete[] m_members;

            m_guildName = other.m_guildName;
            m_size = other.m_size;

            if (other.m_members != nullptr){
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

    Guild& Guild::operator=(Guild&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;
    
            m_guildName = std::move(other.m_guildName);
            m_members = other.m_members;
            m_size = other.m_size;
    
            other.m_members = nullptr;
            other.m_size = 0;
        }
        return *this;
    }
    
    Guild::~Guild() {
        delete[] m_members; 
    }

    void Guild::addMember(Character* c) {
        if (c) {
            for (size_t i = 0; i < m_size; i++) {
                if (m_members[i]->getName() == c->getName()) {
                    return;
                }
            }
        }

        c->setHealthMax(c->getHealthMax() + 300);
        c->setHealth(c->getHealthMax());

        Character** temp = new Character*[m_size + 1];

        for (size_t i = 0; i < m_size; i++) {
            temp[i] = m_members[i];
        }

        temp[m_size] = c;

        delete[] m_members;
        m_members = temp;
        m_size++;
    }

    void Guild::removeMember(const std::string& c) {
        for (size_t i = 0; i < m_size; i++) {
            if (m_members[i]->getName() == c) {

                m_members[i]->setHealthMax(m_members[i]->getHealthMax() - 300);
                if (m_members[i]->getHealth() > m_members[i]->getHealthMax()) {
                    m_members[i]->setHealth(m_members[i]->getHealthMax());
                }

                for (size_t j = i; j < m_size - 1; j++) {
                    m_members[j] = m_members[j + 1];
                }
                m_size--;

                if (m_size > 0) {
                    Character** temp = new Character*[m_size];
                    for (size_t i = 0; i < m_size; i++) {
                        temp[i] = m_members[i];
                    }

                    delete[] m_members;
                    m_members = temp;
                } else {
                    delete[] m_members;
                    m_members = nullptr;
                }
                return;
            }
        }
    }

    Character* Guild::operator[](size_t idx) const {
        if (idx >= m_size) {
            std::cerr << idx << " is out of bounds!" << std::endl;
            return nullptr;
        }
        return m_members[idx];
    }

    void Guild::showMembers() const {
        if (m_guildName == "") {
            std::cout << "No guild." << std::endl;
            return;
        }

        std::cout << "[Guild] " << m_guildName << std::endl;

        for (size_t i = 0; i < m_size; i++) {
            std::cout << "    " << (i + 1) << ": "<< *m_members[i] << std::endl;
        }
    }
}