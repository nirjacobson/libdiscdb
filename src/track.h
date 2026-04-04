#ifndef TRACK_H
#define TRACK_H

#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>

#include <string>
#include <sstream>

namespace DiscDB {

    class Track {
        public:

            class Builder;
            class Fields;

            unsigned int frame_offset() const;
            const std::string& title() const;
            const std::string& extended_data() const;

            std::string to_json() const;
            static Track from_json(const std::string& json);

        private:

            unsigned int _frame_offset;
            std::string _title;
            std::string _extended_data;
    };

    class Track::Builder {

        public:

            Builder& frame_offset(const unsigned int frame_offset);
            Builder& title(const std::string& title);
            Builder& extended_data(const std::string& extended_data);
            Track build() const;

        private:
            Track _track;
    };

    class Track::Fields {
        public:
            static const std::string FrameOffset;
            static const std::string Title;
            static const std::string ExtendedData;
    };

}

#endif // TRACK_H