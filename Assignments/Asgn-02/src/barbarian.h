#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include "characterTpl.h"
namespace seneca {
    template<typename T, typename Abitity_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T> {
        int m_baseDefense{};
        int m_baseAttack{};
        Abitity_t m_ability;
        Weapon_t m_weapon [2];
    public:
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon) 
            : CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense) {
                m_weapon[0] = primaryWeapon;
                m_weapon[1] = secondaryWeapon;
            } 
        
        int getAttackAmnt() const {
            return m_baseAttack + static_cast<int>(static_cast<double>(m_weapons[0]) / 2) + static_cast<int>(static_cast<double>(m_weapons[1]) / 2);
        }

        int getAttackAmnt() const override {
            return m_baseDefense;
        }

        CharacterTpL<T>* clone() const override {
            return new Barbarian<T, Ability_t, Weapon_t>(*this);
        }

        void attack(Character* enemy) override;

        void takeDamage(int dmg) override;
    };
}
#endif