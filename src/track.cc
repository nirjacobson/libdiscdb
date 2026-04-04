#include "track.h"

const std::string DiscDB::Track::Fields::FrameOffset  = "frameOffset";
const std::string DiscDB::Track::Fields::Title        = "title";
const std::string DiscDB::Track::Fields::ExtendedData = "extendedData";

unsigned int DiscDB::Track::frame_offset() const {
    return _frame_offset;
}

const std::string& DiscDB::Track::title() const {
    return _title;
}

const std::string& DiscDB::Track::extended_data() const {
    return _extended_data;
}

std::string DiscDB::Track::to_json() const {
    Json::Value value;

    value[Fields::FrameOffset] = _frame_offset;

    if (!_title.empty())
        value[Fields::Title] = _title;

    if (!_extended_data.empty())
        value[Fields::ExtendedData] = _extended_data;

    std::stringstream ss;
    ss << value;

    return ss.str();
}

DiscDB::Track DiscDB::Track::from_json(const std::string& json) {
    Json::Value value;
    std::stringstream ss(json);
    ss >> value;

    Builder builder;

    builder
    .frame_offset(value[Fields::FrameOffset].asUInt())
    .title(value[Fields::Title].asString())
    .extended_data(value[Fields::ExtendedData].asString());

    return builder.build();
}

DiscDB::Track::Builder& DiscDB::Track::Builder::frame_offset(const unsigned int frame_offset) {
    _track._frame_offset = frame_offset;

    return *this;
}

DiscDB::Track::Builder& DiscDB::Track::Builder::title(const std::string& title) {
    _track._title = title;

    return *this;
}

DiscDB::Track::Builder& DiscDB::Track::Builder::extended_data(const std::string& extended_data) {
    _track._extended_data = extended_data;

    return *this;
}

DiscDB::Track DiscDB::Track::Builder::build() const {
    return _track;
}