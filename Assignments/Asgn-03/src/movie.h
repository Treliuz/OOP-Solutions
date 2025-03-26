/********************************************************************************
* OOP345 – Assignment 03
*
* I declare that this assignment is my own work in accordance with Seneca's
* Academic Integrity Policy:
*
* Name: Joseph Mwamba-Mukuna Student ID: 163997216 Date: 21/03/2025 
********************************************************************************/
#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H
#include "mediaItem.h"
#include "settings.h"
#include <string>
namespace seneca {
    class Movie : public MediaItem {
       Movie(const std::string& title, unsigned short year, const std::string& summary);
    public: 
        void display(std::ostream& out) const override;
        static Movie* createItem(const std::string& strMovie);
    };
}
#endif

