#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H
#include "mediaItem.h"
#include "settings.h"
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <algorithm>

namespace seneca {
    struct TvEpisode {
        const TvShow* m_show{};
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };

    class TvShow : public MediaItem {
        std::string m_id {};
        std::vector<TvEpisode> m_episodes {};
        TvShow(const std::string& showID, const std::string& title, unsigned short year, const std::string& summary);
    public:
        void display(std::ostream& out) const override;
        TvShow* createItem(const std::string& strShow);
        const std::string getId() const;
        template<typename Collection_t>
        void addEpisode(Collection_t& col, const std::string& strEpisode) {
            if (strEpisode.size() == 0 || strEpisode[0] == '#')
                throw "Not a valid episode.";
            
            std::string id, ssEp, ssSeason, ssEpInSeason, airDate, ssLength, title, summary;
            unsigned short ovrEpNum, season, epInSeason;
            unsigned int length, hours, minutes, seconds;
            std::stringstream ss(strEpisode);

            std::getline(ss, id, ',');
            std::getline(ss, ssEp, ',');
            std::getline(ss, ssSeason, ',');
            std::getline(ss, ssEpInSeason, ',');
            std::getline(ss, airDate, ',');
            std::getline(ss, ssLength, ',');
            std::getline(ss, title, ',');
            std::getline(ss, summary);
            trim(id);
            trim(ssEp);
            trim(ssSeason);
            trim(ssEpInSeason);
            trim(airDate);
            trim(ssLength);
            trim(title);
            trim(summary);

            ovrEpNum = static_cast<unsigned short>(std::stoi(ssEp));
            epInSeason = static_cast<unsigned short>(std::stoi(ssEpInSeason));
            season = ssSeason.empty() ? 1 : static_cast<unsigned short>(std::stoi(ssSeason));
            
            std::replace(ssLength.begin(), ssLength.end(), ':', ' ');
            std::stringstream ss(ssLength);
            ss >> hours >> minutes >> seconds;

            length = (hours * 3600) + (minutes * 60) + seconds;

            for (size_t i = 0; i < col.size(); i++) {
                MediaItem* item = col[i];
                if (item && item->getId() == id) {
                    TvShow* showID = dynamic_cast<TvShow*>(item);
                    if (showID){
                        TvEpisode episode = {showID, ovrEpNum, season, epInSeason, airDate, length, title, summary};
                        showID->m_episodes.push_back(episode);
                    }
                    return;
                }
            }

        }

        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;
    };
}
#endif