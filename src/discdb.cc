#include "discdb.h"

DiscDB::Disc DiscDB::query(const ::DiscDB::Disc& disc) {
    const cURLpp::Cleanup cleanup;
    cURLpp::Easy request;

    request.setOpt(new curlpp::options::Url(DiscDB::BaseURL + "/query"));

    std::list<std::string> header;
    header.push_back("Content-Type: application/json");

    request.setOpt(new curlpp::options::HttpHeader(header));

    const std::string json = disc.toJSON();

    std::stringstream ss;
    request.setOpt(new curlpp::options::PostFields(json));
    request.setOpt(new curlpp::options::PostFieldSize(json.size() + 1));
    request.setOpt(cURLpp::Options::WriteStream(&ss));

    request.perform();

    return Disc::fromJSON(ss.str());
}

DiscDB::Disc DiscDB::create(const ::DiscDB::Disc& disc) {
    const cURLpp::Cleanup cleanup;
    cURLpp::Easy request;

    request.setOpt(new curlpp::options::Url(DiscDB::BaseURL));

    std::list<std::string> header;
    header.push_back("Content-Type: application/json");

    request.setOpt(new curlpp::options::HttpHeader(header));

    const std::string json = disc.toJSON();

    std::stringstream ss;
    request.setOpt(new curlpp::options::PostFields(json));
    request.setOpt(new curlpp::options::PostFieldSize(json.size() + 1));
    request.setOpt(cURLpp::Options::WriteStream(&ss));

    request.perform();

    return Disc::fromJSON(ss.str());
}