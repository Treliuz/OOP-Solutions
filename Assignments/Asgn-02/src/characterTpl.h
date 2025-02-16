/********************************************************************************
* OOP345 – Assignment 02
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 02/16/2025 
********************************************************************************/
#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#include "character.h"
namespace seneca {
    template <typename T>
    class CharacterTpl : public Character {
        int m_healthMax{};
        T m_health;
    public:
        CharacterTpl(const char* name, int maxHealth) : Character(name), m_healthMax(maxHealth) {
            m_health = maxHealth;
        }

        void takeDamage(int dmg) override {
            m_health -= dmg;
            if (m_health < 0) {
                m_health = 0; 
            }
            
            if (isAlive() == true){
                std::cout << "    " << getName() << " took " << dmg << " damage, " << m_health << " health remaining." << std::endl;
            } else {
                std::cout << "    " << getName() << " has been defeated!" << std::endl;
            }
        }

        int getHealth() const override {
            return static_cast<int>(m_health);
        }
        int getHealthMax() const override {
            return m_healthMax;
        }
        void setHealth(int health) override {
            m_health = health;
        }
        void setHealthMax(int health) override {
            m_healthMax = health;
        }
    };
}
#endif