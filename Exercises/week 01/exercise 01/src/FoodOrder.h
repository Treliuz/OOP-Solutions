#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H
#include <iostream>
#include <iomanip>

extern double g_taxrate;
extern double g_dailydiscount;

namespace seneca {
    class FoodOrder {
        char m_name[11];
        char* m_desc;
        double m_price;
        bool isSpecial;
    public:
        FoodOrder();
        FoodOrder(const FoodOrder& other);
        FoodOrder& operator=(const FoodOrder& src);
        ~FoodOrder();
        void read(std::istream& is);
        void display() const;
    };
}
#endif
