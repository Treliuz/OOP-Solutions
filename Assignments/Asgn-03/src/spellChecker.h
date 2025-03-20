#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H

#define SIZE 6
#include <string>
namespace seneca {
    class SpellChecker {
        std::string m_badWords[SIZE];
        std::string m_goodWords[SIZE];
        size_t count[SIZE] {};
    public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;
        void trim(std::string& str);
    };
}

#endif