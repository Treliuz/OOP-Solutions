
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "settings.h" // Include the settings module
#include "dictionary.h"

namespace seneca {

    // Default constructor
    Dictionary::Dictionary() {}

    // Constructor that loads words from a file
    Dictionary::Dictionary(const char* filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            m_empty = true;
            return;
        }

        std::vector<Word> tempWords;
        std::string line;
        while (std::getline(file, line)) {
            size_t delimiter = line.find('|');
            if (delimiter == std::string::npos) continue;

            std::string wordStr = trim(line.substr(0, delimiter));
            std::string definitionStr = trim(line.substr(delimiter + 1));

            // Extract part of speech from the definition (if present)
            size_t posStart = definitionStr.find('(');
            size_t posEnd = definitionStr.find(')');
            PartOfSpeech pos = PartOfSpeech::Unknown;
            if (posStart != std::string::npos && posEnd != std::string::npos && posStart < posEnd) {
                std::string posStr = trim(definitionStr.substr(posStart + 1, posEnd - posStart - 1));
                pos = stringToPartOfSpeech(posStr);
                definitionStr = trim(definitionStr.substr(0, posStart) + definitionStr.substr(posEnd + 1));
            }

            tempWords.push_back({wordStr, definitionStr, pos});
        }

        // Allocate memory for the array
        m_size = tempWords.size();
        if (m_size > 0) {
            words = new Word[m_size];
            std::copy(tempWords.begin(), tempWords.end(), words);
            m_empty = false;
        }
    }

    // Destructor
    Dictionary::~Dictionary() {
        delete[] words;
    }

    // Copy constructor
    Dictionary::Dictionary(const Dictionary& other) {
        m_size = other.m_size;
        m_empty = other.m_empty;
        if (m_size > 0) {
            m_words = new Word[m_size];
            std::copy(other.m_words, other.m_words + m_size, m_words);
        } else {
            m_words = nullptr;
        }
    }

    // Copy assignment operator
    Dictionary& Dictionary::operator=(const Dictionary& other) {
        if (this != &other) {
            delete[] m_words;
            m_size = other.m_size;
            m_empty = other.m_empty;
            if (m_size > 0) {
                m_words = new Word[m_size];
                std::copy(other.m_words, other.m_words + m_size, m_words);
            } else {
                m_words = nullptr;
            }
        }
        return *this;
    }

    // Move constructor
    Dictionary::Dictionary(Dictionary&& other) noexcept {
        m_words = other.m_words;
        m_size = other.m_size;
        m_empty = other.m_empty;
        other.m_words = nullptr;
        other.m_size = 0;
        other.m_empty = true;
    }

    // Move assignment operator
    Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
        if (this != &other) {
            delete[] m_words;
            m_words = other.m_words;
            m_size = other.m_size;
            m_empty = other.m_empty;
            other.m_words = nullptr;
            other.m_size = 0;
            other.m_empty = true;
        }
        return *this;
    }

    // Search for a word in the dictionary
    void Dictionary::searchWord(const char* word) const {
        if (m_empty) {
            std::cout << "Dictionary is empty." << std::endl;
            return;
        }

        std::string searchWordStr(word);
        bool found = false;
        for (size_t i = 0; i < m_size; ++i) {
            if (m_words[i].m_word == searchWordStr) {
                if (!found) {
                    std::cout << m_words[i].m_word << " - ";
                    found = true;
                } else {
                    std::cout << std::string(m_words[i].m_word.length() + 3, ' ');
                }

                if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
                    std::cout << "(";
                    switch (m_words[i].m_pos) {
                        case PartOfSpeech::Noun: std::cout << "Noun"; break;
                        case PartOfSpeech::Pronoun: std::cout << "Pronoun"; break;
                        case PartOfSpeech::Adjective: std::cout << "Adjective"; break;
                        case PartOfSpeech::Adverb: std::cout << "Adverb"; break;
                        case PartOfSpeech::Verb: std::cout << "Verb"; break;
                        case PartOfSpeech::Preposition: std::cout << "Preposition"; break;
                        case PartOfSpeech::Conjunction: std::cout << "Conjunction"; break;
                        case PartOfSpeech::Interjection: std::cout << "Interjection"; break;
                        default: break;
                    }
                    std::cout << ") ";
                }

                std::cout << m_words[i].m_definition << std::endl;

                if (!g_settings.m_show_all) break;
            }
        }

        if (!found) {
            std::cout << "Word '" << searchWordStr << "' was not found in the dictionary." << std::endl;
        }
    }

}
