/**
 * @file discdb.h
 * @author Nir Jacobson
 * @date 2026-04-06
 */

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

/// @brief The DiscDB namespace.
/// Contains the DiscDB API methods.
namespace DiscDB {
    const std::string BaseURL = "https://discdb.nirjacobson.com/api/v1.0";

    /// @brief Find a Disc given the minimal set of its information.
    /// @param [in] disc The minimal disc information. This is mostly discId and tracks.frameOffset.
    /// @return A fully populated Disc object (album information).
    Disc find(const Disc& disc);

    /// @brief Save a Disc to DiscDB.
    /// @param [in] disc A fully populated Disc object (album information).
    /// @return The same Disc object with the _id field populated.
    Disc create(const Disc& disc);
}

#endif // DISCDB_H