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

#include <stuff/datetime/datetime.h>
#include <stuff/datetime/financial.h>

namespace stuff::datetime {

    forex_bells get_forex_bells(sys_time t)
    {
        // find sunday in nyc
        zoned_time sunday = find_sunday(date::make_zoned(nyc_tz(), t));

        // compute open and close in nyc
        local_time open  = sunday.get_local_time() + std::chrono::hours(17);
        local_time close = open + date::days(5);

        return forex_bells {date::make_zoned(nyc_tz(), open).get_sys_time(),
            date::make_zoned(nyc_tz(), close).get_sys_time()};
    }

} // namespace stuff::datetime
