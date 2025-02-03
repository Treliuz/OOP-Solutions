/********************************************************************************
* OOP345 – Assignment 01
* Line 52-55 written with help from https://www.geeksforgeeks.org/c-plus-plus/?ref=shm
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 02/02/2025  
********************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "settings.h"
#include "dictionary.h"

namespace seneca {

    std::string Dictionary::POS(PartOfSpeech pos) const {
        switch (pos) {
            case PartOfSpeech::Noun: return "Noun";
            case PartOfSpeech::Pronoun: return "Pronoun";
            case PartOfSpeech::Adjective: return "Adjective";
            case PartOfSpeech::Adverb: return "Adverb";
            case PartOfSpeech::Verb: return "Verb";
            case PartOfSpeech::Preposition: return "Preposition";
            case PartOfSpeech::Conjunction: return "Conjunction";
            case PartOfSpeech::Interjection: return "Interjection";
            default: return "";
        }
    }

    Dictionary::Dictionary() : words(nullptr), size(0) {}

    Dictionary::Dictionary(const char* filename) : words(nullptr), size(0) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return;
        }

        size_t count = 0;
        std::string line;
        while (std::getline(file, line)) {
            count++;
        }

        words = new Word[count];
        size = count;

        file.clear();
        file.seekg(0);

        size_t index = 0;
        while (std::getline(file, line)) {
            if (index < size) {
                std::istringstream iss(line);
                std::string word, pos, definition;
                if (std::getline(iss, word, ',') && std::getline(iss, pos, ',') && std::getline(iss, definition)) {
                    words[index].m_word = word;
                    words[index].m_definition = definition;

                    if (pos == "n." || pos == "n. pl.") {
                        words[index].m_pos = PartOfSpeech::Noun;
                    }
                    else if (pos == "adv.") {
                        words[index].m_pos = PartOfSpeech::Adverb;
                    }
                    else if (pos == "a.") {
                        words[index].m_pos = PartOfSpeech::Adjective;
                    }
                    else if (pos == "v." || pos == "v. i." || pos == "v. t." || pos == "v. t. & i.") {
                        words[index].m_pos = PartOfSpeech::Verb;
                    }
                    else if (pos == "prep.") {
                        words[index].m_pos = PartOfSpeech::Preposition;
                    }
                    else if (pos == "pron.") {
                        words[index].m_pos = PartOfSpeech::Pronoun;
                    }
                    else if (pos == "conj.") {
                        words[index].m_pos = PartOfSpeech::Conjunction;
                    }
                    else if (pos == "interj.") {
                        words[index].m_pos = PartOfSpeech::Interjection;
                    }
                    else {
                        words[index].m_pos = PartOfSpeech::Unknown;
                    }
                    index++;
                }
            }
        }
    }

    Dictionary::~Dictionary() {
        delete[] words;
    }

    Dictionary::Dictionary(const Dictionary& other) : words(nullptr), size(0) {
        if (other.words) {
            size = other.size;
            words = new Word[size];
            for (size_t i = 0; i < size; i++) {
                words[i] = other.words[i];
            }
        }
    }

    Dictionary& Dictionary::operator=(const Dictionary& other) {
        if (this != &other) {
            delete[] words;

            if (other.words) {
                size = other.size;
                words = new Word[size];
                for (size_t i = 0; i < size; ++i) {
                    words[i] = other.words[i];
                }
            } else {
                words = nullptr;
                size = 0;
            }
        }
        return *this;
    }

    Dictionary::Dictionary(Dictionary&& other) noexcept : words(other.words), size(other.size){
        other.words = nullptr;
        other.size = 0;
    }

    Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
        if (this != &other) {
            delete[] words;
            words = other.words;
            size = other.size;
            other.words = nullptr;
            other.size = 0;
        }
        return *this;
    }

    void Dictionary::searchWord(const char* word) const {
        bool found = false;
        for (size_t i = 0; i < size; i++) {
            if (words[i].m_word == word) {
                if (!found) {
                    std::cout << words[i].m_word << " - ";
                    if (g_settings.m_verbose && words[i].m_pos != PartOfSpeech::Unknown) {
                        std::cout << "(" << POS(words[i].m_pos) << ") ";
                    }
                    std::cout << words[i].m_definition << std::endl;
                    found = true;
                } else {
                    std::cout << std::setw(words[i].m_word.length() + 3) << " - ";
                    if (g_settings.m_verbose && words[i].m_pos != PartOfSpeech::Unknown) {
                        std::cout << "(" << POS(words[i].m_pos) << ") ";
                    }
                    std::cout << words[i].m_definition << std::endl;
                }

                if (!g_settings.m_show_all) {
                    break;
                }
            }
        }
        
        if (!found) {
            std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
        }
    }
}
