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
#include <stuff/datetime/types.h>

namespace stuff::datetime {

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

} // namespace stuff::datetime

#endif // STUFF_DATETIME_DATETIME_H
