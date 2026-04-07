/**
 * @file discdb.cc
 * @author Nir Jacobson
 * @date 2026-04-06
 */

 #include "discdb.h"

DiscDB::Disc DiscDB::find(const ::DiscDB::Disc& disc) {
    const cURLpp::Cleanup cleanup;
    cURLpp::Easy request;

    request.setOpt(new curlpp::options::Url(DiscDB::BaseURL + "/find"));

    std::list<std::string> header;
    header.push_back("Content-Type: application/json");

    request.setOpt(new curlpp::options::HttpHeader(header));

    const std::string json = disc.to_json();

    std::stringstream ss;
    request.setOpt(new curlpp::options::PostFields(json));
    request.setOpt(new curlpp::options::PostFieldSize(json.size() + 1));
    request.setOpt(cURLpp::Options::WriteStream(&ss));

    request.perform();

    return Disc::from_json(ss.str());
}

DiscDB::Disc DiscDB::create(const ::DiscDB::Disc& disc) {
    const cURLpp::Cleanup cleanup;
    cURLpp::Easy request;

    request.setOpt(new curlpp::options::Url(DiscDB::BaseURL));

    std::list<std::string> header;
    header.push_back("Content-Type: application/json");

    request.setOpt(new curlpp::options::HttpHeader(header));

    const std::string json = disc.to_json();

    std::stringstream ss;
    request.setOpt(new curlpp::options::PostFields(json));
    request.setOpt(new curlpp::options::PostFieldSize(json.size() + 1));
    request.setOpt(cURLpp::Options::WriteStream(&ss));

    request.perform();

    return Disc::from_json(ss.str());
}