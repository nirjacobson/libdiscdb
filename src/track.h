#ifndef DISCDB_TRACK_H
#define DISCDB_TRACK_H

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

      unsigned int frameOffset() const;
      const std::string& title() const;
      const std::string& extendedData() const;

      std::string toJSON() const;
      static Track fromJSON(const std::string& json);

    private:

      unsigned int _frameOffset;
      std::string _title;
      std::string _extendedData;
  };

  class Track::Builder {
    public:

      Builder& frameOffset(const unsigned int frameOffset);
      Builder& title(const std::string& title);
      Builder& extendedData(const std::string& extendedData);
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

#endif // DISCDB_TRACK_H