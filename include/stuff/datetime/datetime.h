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

#ifndef STUFF_DATETIME_DATETIME_H
#define STUFF_DATETIME_DATETIME_H

#include <chrono>
#include <date/date.h>
#include <date/tz.h>
#include <string>
#include <stuff/core/exception.h>

namespace stuff::datetime {

    STUFF_DEFINE_EXCEPTION(datetime_error, core::generic_error);

    //
    // Aliases for chrono and date lib types.
    // Currently using Howard Hinnant's date libraries which have been accepted
    // for C++20. In the future, these aliases might point to std:: instead.
    //
    // Note the explicit use of nanoseconds: I work with time-series data that
    // is often of nanosecond resolution. On some implementations nanoseconds
    // is the default, this just makes it explicit. Your system's clock may not
    // be that accurate when calling current_time(), but that isn't a problem
    // when processing historical data, for example.
    //
    using clock      = std::chrono::system_clock;
    using duration   = std::chrono::nanoseconds;
    using time_point = std::chrono::time_point<clock, duration>;

    using local_time = date::local_time<duration>;
    using sys_time   = date::sys_time<duration>;

    using sys_days   = date::sys_days;
    using local_days = date::local_days;

    using time_zone  = const date::time_zone*;
    using zoned_time = date::zoned_time<duration, time_zone>;

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
    // Quick access to the New York (US East) time zone struct.
    //
    time_zone nyc_tz() noexcept;

    //
    // Get the current time relative to UTC or the given time zone.
    //
    sys_time   current_time() noexcept;
    zoned_time current_time(time_zone tz);

    //
    // Given any time, find the start of the week (i.e., sunday at midnight).
    //
    sys_time   find_sunday(sys_time t);
    zoned_time find_sunday(zoned_time t);

    //
    // Given a day-point (as sys_time or local_time), find the day-point for the
    // preceding Sunday.
    //
    template <typename T>
    T find_sunday(T dp)
    {
        auto wd = date::weekday(dp);
        if (wd == date::Monday) {
            dp -= date::days(1);
        }
        else if (wd == date::Tuesday) {
            dp -= date::days(2);
        }
        else if (wd == date::Wednesday) {
            dp -= date::days(3);
        }
        else if (wd == date::Thursday) {
            dp -= date::days(4);
        }
        else if (wd == date::Friday) {
            dp -= date::days(5);
        }
        else if (wd == date::Saturday) {
            dp -= date::days(6);
        }

        return dp;
    }

    //
    // Quickly convert the given string to time.
    // The string is expected to be in the following ISO 8601 format:
    //   2020-03-21T09:34:51.123456789Z
    // or
    //   2020-03-21 09:34:51.123456789Z
    // with 'Z' (sys_time) or without 'Z' (sys_time or local_time)
    //
    sys_time   to_sys_time(std::string_view view);
    local_time to_local_time(std::string_view view);

    // Convenience conversions:
    // to sys_time from local string and zone
    sys_time to_sys_time(std::string_view local_view, time_zone local_tz);

    // Quickly convert the given time to a string with nanosecond resolution.
    // The output will be of the form:
    //  2020-03-21T09:34:51.123456789Z (for sys_time)
    //  2020-03-21T09:34:51.123456789  (for local_time)
    //  2020-03-21T09:34:51.123456789 America/New_York (e.g., most of US East)
    std::string to_string(sys_time t);
    std::string to_string(local_time t);
    std::string to_string(zoned_time t);

} // namespace stuff::datetime

#endif // STUFF_DATETIME_DATETIME_H
