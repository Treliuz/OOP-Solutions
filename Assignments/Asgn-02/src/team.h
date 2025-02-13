#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include "character.h"
#include <string>
namespace seneca {
    class Team {
        std::string m_teamName;
        Character** m_members;
        size_t m_size;
    public:
        Team();
        ~Team();
        Team(const char* name);
        Team(const Team& src);
        Team(Team&& src);
        Team& operator=(const Team& src) noexcept;
        Team& operator=(Team&& src) noexcept;
        void addMember(const Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}
#endif