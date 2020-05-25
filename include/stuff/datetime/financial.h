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

#ifndef STUFF_DATETIME_FINANCIAL_H
#define STUFF_DATETIME_FINANCIAL_H

#include <stuff/datetime/types.h>

namespace stuff::datetime {

    // Other than holidays, the foreign exchange open every Sunday at 5:00 PM
    // and closes Friday at 5:00 PM (New York). Given a time, find the
    // corresponding open close for that week.
    struct forex_bells {
        const sys_time open;
        const sys_time close;
    };
    [[nodiscard]] forex_bells get_forex_bells(sys_time t) noexcept;

} // namespace stuff::datetime

#endif // STUFF_DATETIME_FINANCIAL_H
