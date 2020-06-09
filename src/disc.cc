#include "disc.h"

const std::string DiscDB::Disc::Fields::ID           = "_id";
const std::string DiscDB::Disc::Fields::DiscID       = "discId";
const std::string DiscDB::Disc::Fields::Artist       = "artist";
const std::string DiscDB::Disc::Fields::Title        = "title";
const std::string DiscDB::Disc::Fields::Year         = "year";
const std::string DiscDB::Disc::Fields::Genre        = "genre";
const std::string DiscDB::Disc::Fields::Length       = "length";
const std::string DiscDB::Disc::Fields::Tracks       = "tracks";
const std::string DiscDB::Disc::Fields::ExtendedData = "extendedData";
const std::string DiscDB::Disc::Fields::PlayOrder    = "playOrder";

const std::string& DiscDB::Disc::id() const {
    return _id;
}

unsigned int DiscDB::Disc::discId() const {
    return _discId;
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

unsigned int DiscDB::Disc::trackLength(const unsigned int track) const {

    unsigned int index = track - 1;
    unsigned int offset = _tracks[index].frameOffset();

    if (index < (_tracks.size() - 1)) {
        unsigned int nextOffset = _tracks[index + 1].frameOffset();

        return framesToSeconds(nextOffset - offset);
    } else {
        return _length - framesToSeconds(offset);
    }
}

const std::vector<DiscDB::Track>& DiscDB::Disc::tracks() const {
    return _tracks;
}

const std::string& DiscDB::Disc::extendedData() const {
    return _extendedData;
}

std::string DiscDB::Disc::toJSON() const {
    Json::Value value;

    if (!_id.empty())
        value[Fields::ID] = _id;

    value[Fields::DiscID] = _discId;

    if (!_artist.empty())
        value[Fields::Artist] = _artist;

    if (!_title.empty())
        value[Fields::Title] = _title;

    value[Fields::Year] = _year;

    if (!_genre.empty())
        value[Fields::Genre] = _genre;

    value[Fields::Length] = _length;

    Json::Value tracks;
    for (const Track& track : _tracks) {
        std::stringstream ss(track.toJSON());
        Json::Value value;
        ss >> value;

        tracks.append(value);
    }
    value[Fields::Tracks] = tracks;

    if (!_extendedData.empty())
        value[Fields::ExtendedData] = _extendedData;

    Json::Value playOrder;
    for (const unsigned int track : _playOrder)
        playOrder.append(track);
    if (!_playOrder.empty())
        value[Fields::PlayOrder] = playOrder;

    std::stringstream ss;
    ss << value;

    return ss.str();
}

DiscDB::Disc DiscDB::Disc::fromJSON(const std::string& json) {
    Json::Value value;
    std::stringstream ss(json);
    ss >> value;

    Builder builder;

    builder
    .id(value[Fields::ID].asString())
    .discId(value[Fields::DiscID].asUInt())
    .artist(value[Fields::Artist].asString())
    .title(value[Fields::Title].asString())
    .year(value[Fields::Year].asUInt())
    .genre(value[Fields::Genre].asString())
    .length(value[Fields::Length].asUInt())
    .extendedData(value[Fields::ExtendedData].asString());

    for (unsigned int i = 0; i < value[Fields::Tracks].size(); i++) {
        std::stringstream ss;
        ss << value[Fields::Tracks][i];
        builder.track(Track::fromJSON(ss.str()));
    }

    if (!value[Fields::PlayOrder].isNull()) {
        std::vector<unsigned int> playOrder;
        for (unsigned int i = 0; i < value[Fields::PlayOrder].size(); i++)
            playOrder.push_back(value[Fields::Tracks][i].asUInt());
        builder.playOrder(playOrder);
    }

    return builder.build();
}

const std::vector<unsigned int>& DiscDB::Disc::playOrder() const {
    return _playOrder;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::id(const std::string& id) {
    _disc._id = id;

    return *this;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::discId(const unsigned int discId) {
    _disc._discId = discId;

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

DiscDB::Disc::Builder& DiscDB::Disc::Builder::extendedData(const std::string& extendedData) {
    _disc._extendedData = extendedData;

    return *this;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::playOrder(const std::vector<unsigned int>& playOrder) {
    _disc._playOrder = playOrder;

    return *this;
}

DiscDB::Disc::Builder& DiscDB::Disc::Builder::calculateDiscID() {
    if (_disc.tracks().empty()) {
        _disc._discId = 0;
        return *this;
    }

    unsigned int result = 0;
    unsigned int temp;

    for (const Track& track : _disc.tracks()) {
        temp = framesToSeconds(track.frameOffset());
        do {
            result += temp % 10;
            temp /= 10;
        } while (temp != 0);
    }

    _disc._discId =
        ((result % 0xff) << 24)
        | ((_disc._length - framesToSeconds(_disc.tracks()[0].frameOffset()))
           << 8)
        | _disc.tracks().size();

    return *this;
}

DiscDB::Disc DiscDB::Disc::Builder::build() const {
    return _disc;
}