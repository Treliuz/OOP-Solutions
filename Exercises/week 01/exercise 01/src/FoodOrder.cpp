#include "FoodOrder.h"
#include <cstring>

    double g_taxrate = 0;
    double g_dailydiscount = 0;

namespace seneca {
    FoodOrder::FoodOrder() : m_desc{nullptr}, m_price{0.0}, isSpecial{false} {
        m_name[0] = '\0';
        m_desc = new char[200];
    }

    FoodOrder::FoodOrder(const FoodOrder& other) {
        m_desc = new char[200];
        std::strcpy(m_desc, other.m_desc);
        std::strcpy(m_name, other.m_name);
        m_price = other.m_price;
        isSpecial = other.isSpecial;
    }

    FoodOrder& FoodOrder::operator=(const FoodOrder& other) {
        if (this != &other) {
            delete[] m_desc; 
            m_desc = new char[200]; 
            std::strcpy(m_desc, other.m_desc);
            std::strcpy(m_name, other.m_name);
            m_price = other.m_price;
            isSpecial = other.isSpecial;
        }
        return *this;
    }

    void FoodOrder::read(std::istream& is) {
        char c;
        if (is) {
            is.getline(m_name, 10,',');
            is.getline(m_desc, 200,',');
            is >> m_price;
            is.ignore();
            is >> c;
            isSpecial = (c == 'Y');
            is.ignore(1000, '\n');
        }
    }

    void FoodOrder::display() const {
        static int counter {1};
        if (m_name[0] == '\0') {
            std::cout << counter++ << ". No Order" << std::endl;
        } else {
            std::cout << std::left << std::setw(2) << counter++ << ". " << std::setw(10) << m_name << "|" << std::setw(25) << m_desc;
            std::cout << "|" << std::setw(12) << std::fixed << std::setprecision(2) << (m_price + (m_price * g_taxrate)) << "|";
            if (isSpecial)
                std::cout << std::right << std::setw(13) << (m_price + (m_price * g_taxrate)) - g_dailydiscount;
        }
        std::cout << std::endl;
    }

    FoodOrder::~FoodOrder() {
        if (m_desc != nullptr) {
            delete [] m_desc;
            m_desc = nullptr;
        }
    }
}