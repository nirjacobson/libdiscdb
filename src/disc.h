/**
 * @file disc.h
 * @author Nir Jacobson
 * @date 2026-04-06
 */

#ifndef DISC_H
#define DISC_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <json/value.h>

#include "track.h"

namespace DiscDB {

    /// @brief One DiscDB document
    class Disc {

        public:
            /// @brief Disc constructor.
            Disc();

            class Builder;
            class Properties;

            /// @name  Audio Frames
            /// @brief A frame is a duration of audio.
            /**
             * @see   <a href="https://ftp.osuosl.org/pub/netwinder/devteam/andrewm/udf/docs/Glossary_of_CD_terms.pdf"
             *            target="_blank">
             *            A Glossary Of CD And CD-ROM Terms.
             *        </a>
             */
             /// @{
             /// @brief There are 75 audio frames per second.
            static constexpr const unsigned int FRAMES_PER_SECOND = 75;

            /// @brief A convenience method.
            /// @param [in] frames must be a multiple of @ref FRAMES_PER_SECOND.
            /// @{
            static inline unsigned int frames_to_seconds(unsigned int frames) {
                return frames / FRAMES_PER_SECOND;
            }
            /// @}

            /// @name Disc Getters
            /// @{ 
            const std::string& id() const;                              ///< Getter for ::_id.
            unsigned int disc_id() const;                               ///< Getter for ::_disc_id.
            const std::string& artist() const;                          ///< Getter for ::_artist.
            const std::string& title() const;                           ///< Getter for ::_title.
            unsigned int year() const;                                  ///< Getter for ::_year.
            const std::string& genre() const;                           ///< Getter for ::_genre.
            unsigned int length() const;                                ///< Getter for ::_length.

            /// @brief Returns the length in seconds of the given track.
            /// @param [in] track The 1-based index of the track.
            unsigned int track_length(const unsigned int track) const;
            
            const std::vector<Track>& tracks() const;                   ///< Getter for ::_tracks.
            const std::string& extended_data() const;                   ///< Getter for ::_extended_data.
            const std::vector<unsigned int>& play_order() const;        ///< Getter for ::_play_order.
            /// @}

            /// @name JSON Conversion Methods
            /// @{

            /// @brief Converts the Disc to JSON.
            std::string to_json() const;
            /// @brief Builds the Disc from JSON.
            /// @param [in] json The input JSON. 
            /// @return The Disc.
            static Disc from_json(const std::string& json);
            /// @}

        private:

            std::string _id;                       ///< Unique identifier
            unsigned int _disc_id;                 ///< Structural hash
            std::string _artist;                   ///< Album artist
            std::string _title;                    ///< Album title
            unsigned int _year;                    ///< Release year
            std::string _genre;                    ///< Album genre
            unsigned int _length;                  ///< Full length in seconds
            std::vector<Track> _tracks;            ///< Album tracks
            std::string _extended_data;            ///< Footnotes, etc.
            std::vector<unsigned int> _play_order; ///< If different from the track order
    };

    /// @brief The Disc builder
    class Disc::Builder {

        public:

            Builder& id(const std::string& id);                                 ///< Sets Disc::_id.
            Builder& disc_id(const unsigned int disc_id);                       ///< Sets Disc::_disc_id.
            Builder& artist(const std::string& artist);                         ///< Sets Disc::_artist.
            Builder& title(const std::string& title);                           ///< Sets Disc::_title.
            Builder& year(const unsigned int year);                             ///< Sets Disc::_year.
            Builder& genre(const std::string& genre);                           ///< Sets Disc::_genre.
            Builder& length(const unsigned int length);                         ///< Sets Disc::_length.
            Builder& track(const Track& track);                                 ///< Adds to Disc::_tracks.
            Builder& extended_data(const std::string& extended_data);           ///< Sets Disc::_extended_data.
            Builder& play_order(const std::vector<unsigned int>& play_order);   ///< Sets Disc::_play_order.
            Builder& calculate_disc_id();                                       ///< Calculates the disc ID.
            Disc build() const;                                                 ///< Builds the Disc.

        private:

            Disc _disc;                                                         ///< Working Disc.
    };

    /// Disc JSON property names
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