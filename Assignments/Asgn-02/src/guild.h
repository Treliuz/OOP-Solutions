/********************************************************************************
* OOP345 – Assignment 02
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 02/16/2025 
********************************************************************************/
#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#include "character.h"
#include <string>
namespace seneca {
    class Guild {
        std::string m_guildName;
        Character** m_members;
        size_t m_size;
    public:
        Guild();
        Guild(const char* name);
        Guild(const Guild& src);
        Guild(Guild&& src) noexcept;
        Guild& operator=(const Guild& src);
        Guild& operator=(Guild&& src) noexcept;
        ~Guild();
        void addMember(Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}
#endif