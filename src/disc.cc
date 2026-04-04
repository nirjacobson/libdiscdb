#include "disc.h"

const std::string DiscDB::Disc::Fields::Id           = "_id";
const std::string DiscDB::Disc::Fields::DiscId       = "discId";
const std::string DiscDB::Disc::Fields::Artist       = "artist";
const std::string DiscDB::Disc::Fields::Title        = "title";
const std::string DiscDB::Disc::Fields::Year         = "year";
const std::string DiscDB::Disc::Fields::Genre        = "genre";
const std::string DiscDB::Disc::Fields::Length       = "length";
const std::string DiscDB::Disc::Fields::Tracks       = "tracks";
const std::string DiscDB::Disc::Fields::ExtendedData = "extendedData";
const std::string DiscDB::Disc::Fields::PlayOrder    = "playOrder";

DiscDB::Disc::Disc()
    : _year(0)
{

}

const std::string& DiscDB::Disc::id() const {
    return _id;
}

unsigned int DiscDB::Disc::disc_id() const {
    return _disc_id;
}

const std::string& DiscDB::Disc::artist() const {
    return _artist;
}

const std::string& DiscDB::Disc::title() const {
    return _title;
}

unsigned int DiscDB::Disc::year() const {
    return _year;
}

const std::string& DiscDB::Disc::genre() const {
    return _genre;
}

unsigned int DiscDB::Disc::length() const {
    return _length;
}

unsigned int DiscDB::Disc::track_length(const unsigned int track) const {

    unsigned int index = track - 1;
    unsigned int offset = _tracks[index].frame_offset();

    if (index < (_tracks.size() - 1)) {
        unsigned int nextOffset = _tracks[index + 1].frame_offset();

        return frames_to_seconds(nextOffset - offset);
    } else {
        return _length - frames_to_seconds(offset);
    }
}

const std::vector<DiscDB::Track>& DiscDB::Disc::tracks() const {
    return _tracks;
}

const std::string& DiscDB::Disc::extended_data() const {
    return _extended_data;
}

std::string DiscDB::Disc::to_json() const {
    Json::Value value;

    if (!_id.empty())
        value[Fields::Id] = _id;

    std::stringstream sstream;
    sstream.imbue(std::locale("C"));
    sstream << std::hex << _disc_id;
    value[Fields::DiscId] = sstream.str();

    if (!_artist.empty())
        value[Fields::Artist] = _artist;

    if (!_title.empty())
        value[Fields::Title] = _title;

    if (_year != 0) {
        value[Fields::Year] = _year;
    }

    if (!_genre.empty())
        value[Fields::Genre] = _genre;

    value[Fields::Length] = _length;

    Json::Value tracks;
    for (const Track& track : _tracks) {
        std::stringstream ss(track.to_json());
        Json::Value value;
        ss >> value;

        tracks.append(value);
    }
    value[Fields::Tracks] = tracks;

    if (!_extended_data.empty())
        value[Fields::ExtendedData] = _extended_data;

    Json::Value play_order;
    for (const unsigned int track : _play_order)
        play_order.append(track);
    if (!_play_order.empty())
        value[Fields::PlayOrder] = play_order;

    std::stringstream ss;
    ss << value;

    return ss.str();
}

DiscDB::Disc DiscDB::Disc::from_json(const std::string& json) {
    Json::Value value;
    std::stringstream ss(json);
    ss >> value;

    Builder builder;

    unsigned int disc_id;
    std::stringstream sstream;
    sstream << std::hex  << value[Fields::DiscId].asString();
    sstream >> disc_id;

    builder
    .id(value[Fields::Id].asString())
    .disc_id(disc_id)
    .artist(value[Fields::Artist].asString())
    .title(value[Fields::Title].asString())
    .year(value[Fields::Year].asUInt())
    .genre(value[Fields::Genre].asString())
    .length(value[Fields::Length].asUInt())
    .extended_data(value[Fields::ExtendedData].asString());

    for (unsigned int i = 0; i < value[Fields::Tracks].size(); i++) {
        std::stringstream ss;
        ss << value[Fields::Tracks][i];
        builder.track(Track::from_json(ss.str()));
    }

    if (!value[Fields::PlayOrder].isNull()) {
        std::vector<unsigned int> play_order;
        for (unsigned int i = 0; i < value[Fields::PlayOrder].size(); i++)
            play_order.push_back(value[Fields::Tracks][i].asUInt());
        builder.play_order(play_order);
    }

    return builder.build();
}

const std::vector<unsigned int>& DiscDB::Disc::play_order() const {
    return _play_order;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::id(const std::string& id) {
    _disc._id = id;

    return *this;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::disc_id(const unsigned int disc_id) {
    _disc._disc_id = disc_id;

    return *this;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::artist(const std::string& artist) {
    _disc._artist = artist;

    return *this;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::title(const std::string& title) {
    _disc._title = title;

    return *this;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::year(const unsigned int year) {
    _disc._year = year;

    return *this;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::genre(const std::string& genre) {
    _disc._genre = genre;

    return *this;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::length(const unsigned int length) {
    _disc._length = length;

    return *this;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::track(const DiscDB::Track& track) {
    _disc._tracks.push_back(track);

    return *this;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::extended_data(const std::string& extended_data) {
    _disc._extended_data = extended_data;

    return *this;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::play_order(const std::vector<unsigned int>& play_order) {
    _disc._play_order = play_order;

    return *this;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::calculate_disc_id() {
    if (_disc.tracks().empty()) {
        _disc._disc_id = 0;
        return *this;
    }

    unsigned int result = 0;
    unsigned int temp;

    for (const Track& track : _disc.tracks()) {
        temp = frames_to_seconds(track.frame_offset());
        do {
            result += temp % 10;
            temp /= 10;
        } while (temp != 0);
    }

    _disc._disc_id =
        ((result % 0xff) << 24)
        | ((_disc._length - frames_to_seconds(_disc.tracks()[0].frame_offset()))
           << 8)
        | _disc.tracks().size();

    return *this;
}

DiscDB::Disc DiscDB::Disc::Builder::build() const {
    return _disc;
}