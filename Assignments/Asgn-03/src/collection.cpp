#include "collection.h"
#include <algorithm>
namespace seneca {
    Collection::Collection(const std::string& name) : m_name(name), observe(nullptr) {}

    Collection::~Collection() {
        for (auto& item : m_items) {
            delete item;
        }
    }

    const std::string& Collection::name() const {
        return m_name;
    }

    size_t Collection::size() const {
        return m_items.size();
    }

    void Collection::setObserver(void (*observer)(const Collection&, const MediaItem&)) {
        observe = observer;
    }

    Collection& Collection::operator+=(MediaItem* item) {
        auto it = std::find_if(m_items.begin(), m_items.end(), [&](MediaItem* src) {
            return src->getTitle() == item->getTitle();
        });

        if (it != m_items.end()) {
            delete item;
        } else {
            m_items.push_back(item);
            if (observe != nullptr) {
                observe(*this, *item);
            }
        }
        return *this;
    }

    MediaItem* Collection::operator[](size_t idx) const {
        if (idx >= m_items.size()) {
            throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_items.size()) + "] items.");
        }
        return m_items[idx];
    }

    MediaItem* Collection::operator[](const std::string& title) const {
        auto it = std::find_if(m_items.begin(), m_items.end(), [&title] (MediaItem* item) {
            return item->getTitle() == title;
        });

        if (it != m_items.end()) {
            return *it;
        } else {
            return nullptr;
        }
    }

    void Collection::removeQuotes() {
        std::for_each(m_items.begin(), m_items.end(), [](MediaItem* item) {
            std::string title = item->getTitle();
            std::string summary = item->getSummary();

            auto fixedString = [] (std::string& str) {
                if (!str.empty() && str.front() == '"' && str.back() == '"') {
                    str = str.substr(1, str.size() - 2);
                }
            };

            fixedString(title);
            item->setTitle(title);
            fixedString(summary);
            item->setSummary(summary);
        });
    }

    void Collection::sort(const std::string& field) {
        if (field == "title") {
            std::sort(m_items.begin(), m_items.end(), [](MediaItem* a, MediaItem* b) {
                return a->getTitle() < b->getTitle();
            });
        } else if (field == "year") {
            std::sort(m_items.begin(), m_items.end(), [](MediaItem* a, MediaItem* b) {
                return a->getYear() < b->getYear();
            });
        }
    }

    std::ostream& operator<<(std::ostream& os, const Collection& col) {
        for (auto& item : col.m_items) {
            os << *item;
        }
        return os;
    }
}