/********************************************************************************
* OOP345 – Assignment 02
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 02/16/2025 
********************************************************************************/
#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include "characterTpl.h"
#include "weapons.h"
#include "abilities.h"
#include <iostream>
namespace seneca {
    template<typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> {
        int m_baseAttack{};
        int m_baseDefense{};
        Ability_t m_ability;
        Weapon_t m_weapon [2];
    public:
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon) 
            : CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense){
                m_weapon[0] = primaryWeapon;
                m_weapon[1] = secondaryWeapon;
        } 
        
        int getAttackAmnt() const override{
            return m_baseAttack + (m_weapon[0] / 2) + (m_weapon[1] / 2);
        }

        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        Character* clone() const override {
            return new Barbarian<T, Ability_t, Weapon_t>(*this);
        }

        void attack(Character* enemy) override { 
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;
            
            m_ability.useAbility(static_cast<Character*>(this));
            int dmg = getAttackAmnt();
            m_ability.transformDamageDealt(dmg);

            std::cout << "    Barbarian deals " << dmg << " melee damage!" << std::endl;

            enemy->takeDamage(dmg);
        }   

        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "    Barbarian has a defense of " << this->m_baseDefense << ". Reducing damage received." << std::endl;

            dmg -= m_baseDefense;
            if (dmg < 0)
                dmg = 0;
            m_ability.transformDamageReceived(dmg);
            CharacterTpl<T>::takeDamage(dmg);
        }
    };
}
#endif