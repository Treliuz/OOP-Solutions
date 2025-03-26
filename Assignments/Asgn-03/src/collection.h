/********************************************************************************
* OOP345 – Assignment 03
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 21/03/2025 
********************************************************************************/
#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include "mediaItem.h"
#include <vector>
#include <string>
namespace seneca {
    class Collection {
        std::string m_name;
        std::vector<MediaItem*> m_items;
        void (*observe)(const Collection&, const MediaItem&);
    public:
        Collection(const std::string& name);
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;
        Collection(Collection&&) = delete;
        Collection& operator=(Collection&&) = delete;
        ~Collection();
        const std::string& name() const;
        size_t size() const;
        void setObserver(void (*observer)(const Collection&, const MediaItem&));
        Collection& operator+=(MediaItem* item);
        MediaItem* operator[](size_t idx) const;
        MediaItem* operator[](const std::string& title) const;
        void removeQuotes();
        void sort(const std::string& field);
        friend std::ostream& operator<<(std::ostream& os, const Collection& col);
    };
}

#endif