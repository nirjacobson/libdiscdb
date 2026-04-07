#ifndef DISC_H
#define DISC_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <json/value.h>

#include "track.h"

namespace DiscDB {

    /**
     * @brief The Disc class
     * @details The Disc class represents one disc record in the DiscDB database.
    */
    class Disc {

        public:
            Disc();

            class Builder;
            class Properties;

            /**
             * @name  Audio Frames
             * @brief A frame is a duration of audio.
             * @see   <a href="https://ftp.osuosl.org/pub/netwinder/devteam/andrewm/udf/docs/Glossary_of_CD_terms.pdf"
             *            target="_blank">
             *            A Glossary Of CD And CD-ROM Terms.
             *        </a>
             * @{
             */

             /**
             * @brief There are 75 audio frames per second.
             */
            static constexpr const unsigned int FRAMES_PER_SECOND = 75;

            /**
             * @brief A convenience method.
             * @param [in] frames must be a multiple of @ref FRAMES_PER_SECOND.
             * 
             * @{
             */
            static inline unsigned int frames_to_seconds(unsigned int frames) {
                return frames / FRAMES_PER_SECOND;
            }
            /**
             * @}
             */

            const std::string& id() const;
            unsigned int disc_id() const;
            const std::string& artist() const;
            const std::string& title() const;
            unsigned int year() const;
            const std::string& genre() const;
            unsigned int length() const;
            unsigned int track_length(const unsigned int track) const;
            const std::vector<Track>& tracks() const;
            const std::string& extended_data() const;
            const std::vector<unsigned int>& play_order() const;

            /**
             * @name JSON Conversion Methods
             * 
             * @{
             */
            std::string to_json() const;
            static Disc from_json(const std::string& json);
            /**
             * @}
             */

        private:

            std::string _id;
            unsigned int _disc_id;
            std::string _artist;
            std::string _title;
            unsigned int _year;
            std::string _genre;
            unsigned int _length;
            std::vector<Track> _tracks;
            std::string _extended_data;
            std::vector<unsigned int> _play_order;
    };

    /**
     * @brief The Disc builder
     * @details Use the builder to construct a Disc object with your chosen property values.
    */
    class Disc::Builder {

        public:

            Builder& id(const std::string& id);
            Builder& disc_id(const unsigned int disc_id);
            Builder& artist(const std::string& artist);
            Builder& title(const std::string& title);
            Builder& year(const unsigned int year);
            Builder& genre(const std::string& genre);
            Builder& length(const unsigned int length);
            Builder& track(const Track& track);
            Builder& extended_data(const std::string& extended_data);
            Builder& play_order(const std::vector<unsigned int>& play_order);
            Builder& calculate_disc_id();
            Disc build() const;

        private:

            Disc _disc;
    };

    /**
     * @brief Disc properties
     * @details These constants are used to access property values in the JSON representation of a Disc.
    */
    class Disc::Properties {
        public:
            static const std::string Id;
            static const std::string DiscId;
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