/**
 * @file track.h
 * @author Nir Jacobson
 * @date 2026-04-06
 */

#ifndef TRACK_H
#define TRACK_H

#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>

#include <string>
#include <sstream>

namespace DiscDB {

    /// @brief One Disc track.
    class Track {
        public:

            class Builder;
            class Properties;

            /// @name Track Getters
            /// @{ 
            unsigned int frame_offset() const;          ///< Getter for _frame_offset.
            const std::string& title() const;           ///< Getter for _title.
            const std::string& extended_data() const;   ///< Getter for _extended_data.
            /// @}

            /// @name JSON Conversion Methods
            /// @{
            
            /// @brief Converts the Track to JSON.
            std::string to_json() const;
            /// @brief Builds the Track from JSON.
            /// @param [in] json The input JSON. 
            /// @return The Track.
            static Track from_json(const std::string& json);
            /// @}

        private:

            /// @brief The offset of the track on the disc in frames.
            unsigned int _frame_offset;
            std::string _title;          ///< Track title (as it appears on the leaf)
            std::string _extended_data;  ///< Footnotes, etc.
    };

    /// @brief The Track builder
    class Track::Builder {

        public:

            Builder& frame_offset(const unsigned int frame_offset);     ///< Sets Track::_frame_offset.
            Builder& title(const std::string& title);                   ///< Sets Track::_title.
            Builder& extended_data(const std::string& extended_data);   ///< Sets Track::_extended_data.
            Track build() const;                                        ///< Builds the Track.

        private:
            Track _track;                                               ///< Working Track.
    };

    /// Track JSON property names
    class Track::Properties {
        public:
            static const std::string FrameOffset;
            static const std::string Title;
            static const std::string ExtendedData;
    };

}

#endif // TRACK_H