#include "tvShow.h"
#include <iostream>
#include <iomanip>
#include <numeric>

namespace seneca {
    TvShow::TvShow(const std::string& id, const std::string& title, unsigned short year, const std::string& summary) : m_id(id), MediaItem(title, summary, year) {}

    void TvShow::display(std::ostream& out) const {
        if (g_settings.m_tableView) {
            out << "S | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_episodes.size() << " | ";
            out << std::setw(4) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1) {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            } else
                out << this->getSummary();
                out << std::endl;
        } else {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size()) {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            for (auto& item : m_episodes) {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                    << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                if (item.m_title != "")
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';
                pos = 0;
                while (pos < item.m_summary.size()) {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
            << std::setfill(' ') << '\n';
        }
    }
    
    TvShow* TvShow::createItem(const std::string& strShow) {
        if (strShow.size() == 0 || strShow[0] == '#')
            throw "Not a valid show.";
        
        std::string id, title, summary, ssYear;
        std::stringstream ss(strShow);
        unsigned short year;

        std::getline(ss, id, ',');
        std::getline(ss, title, ',');
        std::getline(ss, ssYear, ',');
        std::getline(ss, summary);
        trim(id);
        trim(title);
        trim(ssYear);
        trim(summary);

        year = static_cast<unsigned short>(std::stoi(ssYear));

        return new TvShow(id, title, year, summary);
    }

    const std::string TvShow::getId() const {
        return m_id;
    }

    double TvShow::getEpisodeAverageLength() const {
        double totalLen = std::accumulate(m_episodes.begin(), m_episodes.end(), 0.0, [] (double sum, const TvEpisode& ep) {
            return sum + ep.m_length;
        });
        return totalLen / m_episodes.size();
    }

    std::list<std::string> TvShow::getLongEpisodes() const{
        std::list<std::string> longEp;

        std::transform(m_episodes.begin(), m_episodes.end(), std::back_inserter(longEp), [] (const TvEpisode& ep) {
            return ep.m_length >= 3600 ? ep.m_title : "";
        });

        longEp.remove_if([] (const std::string& title){
            return title.empty();
        });
        return longEp;
    }
}