#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H
namespace seneca {
    template<typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
        int m_baseDefense{};
        int m_baseAttack{};
        FirstAbility_t m_firstAbility;
        SecondAbility_t m_secondAbility;
        seneca::Dagger m_weapon;
    public:
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense) : CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense) {}

        int getAttackAmnt() const override {
            return (m_baseAttack + 2 * static_cast<double>m_weapon.m_damage);
        }

        int getDefenseAmnt() const override {
            return m_baseDefense;
        }

        Character* clone() const override {
            return new Rogue<T, FirstAbility_t, SecondAbility_t>(*this);
        }

        void attack(Character* enemy) override {
            std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

            m_firstAbility.useAbility(*this);
            m_secondAbility.useAbility(*this);

            int dmg = getAttackAmnt();

            m_firstAbility.transformDamageDealt(dmg);
            m_secondAbility.transformDamageDealt(dmg);

            std::cout << "Rogue deals " << dmg << " melee damage!" << std::endl;

            enemy->takeDamage(dmg);
        }

        void takeDamage(int dmg) override {
            std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
            std::cout << "\t Rogue has a defense of " << this->m_baseDefense << ". Reducing damage received." << std::endl;

            dmg -= m_baseDefense;
            if (dmg < 0)
                dmg = 0;
            m_firstAbility.transformDamageReceived(dmg);
            m_secondAbility.transformDamageReceived(dmg);
            CharacterTpl<T>::takeDamage(dmg);
        }
    };
}
#endif