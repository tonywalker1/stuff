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

#include <date/date.h>
#include <stuff/datetime/datetime.h>

namespace stuff::datetime {

    time_zone nyc_tz() noexcept
    {
        static const auto tz = date::locate_zone("America/New_York");
        return tz;
    }

    sys_time current_time() noexcept { return clock::now(); }

    zoned_time current_time(time_zone tz)
    {
        return date::make_zoned(tz, clock::now());
    }

    sys_time find_sunday(sys_time t)
    {
        return find_sunday(date::floor<date::days>(t));
    }

    zoned_time find_sunday(zoned_time t)
    {
        return date::make_zoned(t.get_time_zone(),
            find_sunday(date::floor<date::days>(t.get_local_time())));
    }

} // namespace stuff::datetime
