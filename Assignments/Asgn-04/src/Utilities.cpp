//Lines 38-44 we're taken from Stack Overflow
#include "Utilities.h"
#include <stdexcept>

namespace seneca {
    char seneca::Utilities::m_delimiter = ',';
    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        if (next_pos >= str.length()) {
            more = false;
            return "";
        }

        std::string token;
        size_t pos = str.find(m_delimiter, next_pos);

        if (pos == next_pos) {
            next_pos = pos + 1;
            more = false;
            throw std::invalid_argument("ERROR: No token.");
        }

        if (pos != std::string::npos) {
            token = str.substr(next_pos, pos - next_pos);
            next_pos = pos + 1;
        } else {
            token = str.substr(next_pos);
            next_pos = str.length();
        }

        size_t first = token.find_first_not_of(' ');
        size_t last = token.find_last_not_of(' ');
        if (first != std::string::npos) {
            token = token.substr(first, last - first + 1);
        } else {
            token = "";
        }

        if (m_widthField < token.length()) {
            m_widthField = token.length();
        }   
        
        more = (next_pos < str.length());

        return token;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }
}