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

#ifndef STUFF_DATETIME_TYPES_H
#define STUFF_DATETIME_TYPES_H

#include <chrono>
#include <date/date.h>
#include <date/tz.h>

namespace stuff::datetime {

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

} // namespace stuff::datetime

#endif // STUFF_DATETIME_TYPES_H
