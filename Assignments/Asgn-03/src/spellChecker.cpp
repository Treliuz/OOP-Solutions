/********************************************************************************
* OOP345 – Assignment 03
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 21/03/2025 
********************************************************************************/
#include "spellChecker.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
namespace seneca {
    SpellChecker::SpellChecker(const char* filename) {
        std::ifstream file(filename);
        if (file) {
            std::string line;
            size_t i = 0;
            while (std::getline(file, line) && i < SIZE) {
                std::stringstream ss(line);
                std::string bad, good;
                ss >> bad >> good;
                trim(bad);
                trim(good);
                m_badWords[i] = bad;
                m_goodWords[i] = good;
                i++;
            }   
        } else 
            throw "Bad file name!";
    }

    void SpellChecker::trim(std::string& str) {
        size_t i = 0u;
        for (i = 0u; i < str.length() && str[i] == ' '; ++i);
        str = str.substr(i);

        for (i = str.length(); i > 0 && str[i - 1] == ' '; --i);
        str = str.substr(0, i);
    }

    void SpellChecker::operator()(std::string& text) {
        for (size_t i = 0; i < SIZE; ++i) {
            size_t pos = 0;
            while ((pos = text.find(m_badWords[i], pos)) != std::string::npos) {
                text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                count[i]++;
                pos += m_goodWords[i].length();
            };
        }
    }

    void SpellChecker::showStatistics(std::ostream& out) const {
        std::cout << "Spellchecker Statistics" << std::endl;
        for (int i = 0; i < 6; ++i) {
            out << std::left << std::setw(15) << m_badWords[i] << ": " << count[i] << " replacements" << std::endl;  
        }
    }
}