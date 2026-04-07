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

            unsigned int frame_offset() const;
            const std::string& title() const;
            const std::string& extended_data() const;

            /// @name JSON Conversion Methods
            /// @{
            std::string to_json() const;
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

            Builder& frame_offset(const unsigned int frame_offset);
            Builder& title(const std::string& title);
            Builder& extended_data(const std::string& extended_data);
            Track build() const;

        private:
            Track _track;
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