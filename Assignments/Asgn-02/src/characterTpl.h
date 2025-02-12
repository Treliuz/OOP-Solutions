#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#include "character.h"


namespace seneca {
    template <typename T>
    class CharacterTpl : public Character {
        int m_healthMax{};
        T m_health;
    public:
        CharacterTpl(const char* name, int maxHealth) : Character(name), m_healthMax(maxHealth), m_health(maxHealth){}

        void takeDamage(int dmg) override {
            m_health -= dmg;
            if (isAlive() == true){
                std::cout << getName() << " took " << dmg << " damage, " << m_health << " health remaining." << std::endl;
            } else {
                std::cout << getName() << " has been defeated!" << std::endl;
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