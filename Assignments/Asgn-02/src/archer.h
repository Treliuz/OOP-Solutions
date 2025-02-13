#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H
#include "characterTpl.h"
namespace seneca {
    template<typename Weapon_t>
    class Archer : public CharacterTpl<seneca::SuperHealth> {
        int m_baseDefense{};
        int m_baseAttack{};
        Weapon_t m_weapon;
    public:
        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon) : CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense), m_weapon(weapon) {}
        
        int getAttackAmnt() const override {
            return (1.3 * m_baseAttack);
        }

        int getDefenseAmnt() const override {
            return (1.2 * m_baseDefense);
        }

        Character* clone() const override {
            return new Archer<Weapon_t>(*this);
        }

        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            int dmg = getAttackAmnt();

            std::cout << "Archer deals " << dmg << " ranged damage!" << std::endl;
            enemy->takeDamage(dmg);
        }

        void takeDamage(int dmg) {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "\t Archer has a defense of " << this->m_baseDefense << ". Reducing damage received." << std::endl;

            dmg -= m_baseDefense;
            if (dmg < 0)
                dmg = 0;
            m_ability.transformDamageReceived(dmg);
            CharacterTpl<T>::takeDamage(dmg);
        }
    };
}
#endif