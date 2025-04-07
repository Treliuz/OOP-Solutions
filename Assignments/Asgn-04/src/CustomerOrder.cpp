/********************************************************************************
* OOP345 – Assignment 04
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 06/04/2025  
********************************************************************************/
#include "CustomerOrder.h"
#include "Utilities.h"
#include <algorithm>
#include <iostream>
#include <iomanip>

namespace seneca {
    size_t CustomerOrder::m_widthField = 0;
    CustomerOrder::CustomerOrder() : m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr)  {}

    CustomerOrder::CustomerOrder(const std::string& str) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        m_name = util.extractToken(str, next_pos, more);
        m_product = util.extractToken(str, next_pos, more);
        size_t temp = next_pos;
        while (more) {
            util.extractToken(str, temp, more);
            m_cntItem++;
        }

        m_lstItem = new Item*[m_cntItem];
        for (size_t i = 0; i < m_cntItem; ++i) {
            std::string item = util.extractToken(str, next_pos, more);
            m_lstItem[i] = new Item(item);
        }

        if (m_widthField < util.getFieldWidth()) {
            m_widthField = util.getFieldWidth();
        }
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept : m_name(std::move(other.m_name)), m_product(std::move(other.m_product))
        , m_cntItem(other.m_cntItem)
        , m_lstItem(other.m_lstItem) {
        other.m_lstItem = nullptr;
        other.m_cntItem = 0;
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < m_cntItem; i++) {
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            m_name = std::move(other.m_name);
            m_product = std::move(other.m_product);
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;
            other.m_cntItem = 0;
            other.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for (size_t i = 0; i < m_cntItem; i++) {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        return std::all_of(m_lstItem, m_lstItem + m_cntItem, [](const Item* item) {
            return item->m_isFilled;
        });
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        bool allFilled = true;
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == itemName) {
                if (!m_lstItem[i]->m_isFilled) {
                    allFilled = false;
                }
            }
        }
        return allFilled;
    }


    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    m_lstItem[i]->m_isFilled = true;
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    station.updateQuantity();
                    os << "    Filled " << m_name << ", " << m_product 
                       << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                } else {
                    os << "    Unable to fill " << m_name << ", " << m_product 
                       << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
                return;
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++) {
            os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
            os << std::setw(m_widthField) << std::left << std::setfill(' ') << m_lstItem[i]->m_itemName << " - ";
            os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }
}