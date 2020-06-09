#include "track.h"

const std::string DiscDB::Track::Fields::FrameOffset  = "frameOffset";
const std::string DiscDB::Track::Fields::Title        = "title";
const std::string DiscDB::Track::Fields::ExtendedData = "extendedData";

unsigned int DiscDB::Track::frameOffset() const {
    return _frameOffset;
}

const std::string& DiscDB::Track::title() const {
    return _title;
}

const std::string& DiscDB::Track::extendedData() const {
    return _extendedData;
}

std::string DiscDB::Track::toJSON() const {
    Json::Value value;

    value[Fields::FrameOffset] = _frameOffset;

    if (!_title.empty())
        value[Fields::Title] = _title;

    if (!_extendedData.empty())
        value[Fields::ExtendedData] = _extendedData;

    std::stringstream ss;
    ss << value;

    return ss.str();
}

DiscDB::Track DiscDB::Track::fromJSON(const std::string& json) {
    Json::Value value;
    std::stringstream ss(json);
    ss >> value;

    Builder builder;

    builder
    .frameOffset(value[Fields::FrameOffset].asUInt())
    .title(value[Fields::Title].asString())
    .extendedData(value[Fields::ExtendedData].asString());

    return builder.build();
}

DiscDB::Track::Builder& DiscDB::Track::Builder::frameOffset(const unsigned int frameOffset) {
    _track._frameOffset = frameOffset;

    return *this;
}

DiscDB::Track::Builder& DiscDB::Track::Builder::title(const std::string& title) {
    _track._title = title;

    return *this;
}

DiscDB::Track::Builder& DiscDB::Track::Builder::extendedData(const std::string& extendedData) {
    _track._extendedData = extendedData;

    return *this;
}

DiscDB::Track DiscDB::Track::Builder::build() const {
    return _track;
}