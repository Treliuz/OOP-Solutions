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

    Team& Team::operator=(const Team& other) {
        if (this != &other) {

            m_teamName = other.m_teamName;
            m_size = other.m_size;

            for (size_t i = 0; i < m_size; ++i) {
                delete m_members[i];
            }
            delete[] m_members;
    
            m_members = new Character*[m_size];
            for (size_t i = 0; i < m_size; ++i) {
                m_members[i] = other.m_members[i]->clone();
            }
        }
        return *this;
    }

    Team::Team(Team&& other) noexcept : m_teamName(std::move(other.m_teamName)), m_members(other.m_members), m_size(other.m_size) {
        other.m_members = nullptr;
        other.m_size = 0;
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
}