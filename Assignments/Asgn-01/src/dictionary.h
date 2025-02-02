#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H
namespace seneca {
    enum class PartOfSpeech {
        Unknown,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Verb,
        Preposition,
        Conjunction,
        Interjection,
    };

    struct Word {
        std::string m_word{};
        std::string m_definition{};
        PartOfSpeech m_pos = PartOfSpeech::Unknown;
    };

    class Dictionary {
        Word* words{};
        size_t numWords{};
        bool m_empty = true;

        PartOfSpeech stringToPartOfSpeech(const std::string& posStr) const {
            if (posStr == "n." || posStr == "n. pl.") return PartOfSpeech::Noun;
            if (posStr == "adv.") return PartOfSpeech::Adverb;
            if (posStr == "a.") return PartOfSpeech::Adjective;
            if (posStr == "v." || posStr == "v. i." || posStr == "v. t." || posStr == "v. t. & i.") return PartOfSpeech::Verb;
            if (posStr == "prep.") return PartOfSpeech::Preposition;
            if (posStr == "pron.") return PartOfSpeech::Pronoun;
            if (posStr == "conj.") return PartOfSpeech::Conjunction;
            if (posStr == "interj.") return PartOfSpeech::Interjection;
            return PartOfSpeech::Unknown;
        }

        std::string trim(const std::string& str) const {
            auto start = str.begin();
            while (start != str.end() && std::isspace(*start)) start++;
            auto end = str.end();
            do {
                end--;
            } while (std::distance(start, end) > 0 && std::isspace(*end));
            return std::string(start, end + 1);
        }
    public:
        Dictionary();
        Dictionary(const char* filename);
        ~Dictionary();
        Dictionary(const Dictionary& other);
        Dictionary& operator=(const Dictionary& other);
        Dictionary(Dictionary&& other) noexcept;
        Dictionary& operator=(Dictionary&& other) noexcept;
        void searchWord(const char* word) const;
    };
}
#endif