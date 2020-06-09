#ifndef DISCDB_H
#define DISCDB_H

#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>
#include <iostream>

#include "disc.h"

namespace DiscDB {
    const std::string BaseURL = "http://discdb.discdb.io/api/v1.0";

    Disc query(const Disc& disc);
    Disc create(const Disc& disc);
}

#endif // DISCDB_H