#ifndef DISC_H
#define DISC_H

#include <string>
#include <vector>
#include <json/value.h>

#include "track.h"

namespace DiscDB {

    class Disc {

        public:

            class Builder;
            class Fields;

            static constexpr const unsigned int FRAMES_PER_SECOND = 75;
            static inline unsigned int framesToSeconds(unsigned int frames) {
                return frames / FRAMES_PER_SECOND;
            }

            const std::string& id() const;
            unsigned int discId() const;
            const std::string& artist() const;
            const std::string& title() const;
            unsigned int year() const;
            const std::string& genre() const;
            unsigned int length() const;
            unsigned int trackLength(const unsigned int track) const;
            const std::vector<Track>& tracks() const;
            const std::string& extendedData() const;
            const std::vector<unsigned int>& playOrder() const;

            std::string toJSON() const;
            static Disc fromJSON(const std::string& json);

        private:

            std::string _id;
            unsigned int _discId;
            std::string _artist;
            std::string _title;
            unsigned int _year;
            std::string _genre;
            unsigned int _length;
            std::vector<Track> _tracks;
            std::string _extendedData;
            std::vector<unsigned int> _playOrder;
    };

    class Disc::Builder {
        
        public:

            Builder& id(const std::string& id);
            Builder& discId(const unsigned int discId);
            Builder& artist(const std::string& artist);
            Builder& title(const std::string& title);
            Builder& year(const unsigned int year);
            Builder& genre(const std::string& genre);
            Builder& length(const unsigned int length);
            Builder& track(const Track& track);
            Builder& extendedData(const std::string& extendedData);
            Builder& playOrder(const std::vector<unsigned int>& playOrder);
            Builder& calculateDiscID();
            Disc build() const;

        private:

            Disc _disc;
    };

    class Disc::Fields {
        public:
            static const std::string ID;
            static const std::string DiscID;
            static const std::string Artist;
            static const std::string Title;
            static const std::string Year;
            static const std::string Genre;
            static const std::string Length;
            static const std::string Tracks;
            static const std::string ExtendedData;
            static const std::string PlayOrder;
    };
}

#endif // DISC_H