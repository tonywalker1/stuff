//
// Copyright (C) 2020  Tony Walker
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef STUFF_DATETIME_CONVERSIONS_H
#define STUFF_DATETIME_CONVERSIONS_H

#include <string_view>
#include <stuff/core/exception.h>
#include <stuff/datetime/types.h>

namespace stuff::datetime {

    STUFF_DEFINE_EXCEPTION(datetime_error, core::generic_error);

    //
    // Helper's for this library. Do not call from outside this library.
    //
    namespace detail {

        [[nodiscard]] date::year  to_year(std::string_view view);
        [[nodiscard]] date::month to_month(std::string_view view);
        [[nodiscard]] date::day   to_day(std::string_view view);

        [[nodiscard]] duration to_hours(std::string_view view);
        [[nodiscard]] duration to_minutes(std::string_view view);
        [[nodiscard]] duration to_seconds(std::string_view view);
        [[nodiscard]] duration to_nanoseconds(std::string_view view);

    } // namespace detail

    //
    // Quickly convert the given string to time.
    // The string is expected to be in the following ISO 8601 format:
    //   2020-03-21T09:34:51.123456789Z
    // or
    //   2020-03-21 09:34:51.123456789Z
    // with 'Z' (sys_time) or without 'Z' (sys_time or local_time)
    //
    [[nodiscard]] sys_time   to_sys_time(std::string_view view);
    [[nodiscard]] local_time to_local_time(std::string_view view);

    // Convenience conversions:
    // to sys_time from local string and zone
    [[nodiscard]] sys_time to_sys_time(
        std::string_view local_view, time_zone local_tz);

    // Quickly convert the given time to a string with nanosecond resolution.
    // The output will be of the form:
    //  2020-03-21T09:34:51.123456789Z (for sys_time)
    //  2020-03-21T09:34:51.123456789  (for local_time)
    //  2020-03-21T09:34:51.123456789 America/New_York (e.g., most of US East)
    [[nodiscard]] std::string to_string(sys_time t);
    [[nodiscard]] std::string to_string(local_time t);
    [[nodiscard]] std::string to_string(zoned_time t);

} // namespace stuff::datetime

#endif // STUFF_DATETIME_CONVERSIONS_H
