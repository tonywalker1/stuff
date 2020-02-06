// Copyright (C) 2019, 2020  Tony Walker
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

#ifndef STUFF_CORE_UNITS_H
#define STUFF_CORE_UNITS_H

#include <cstddef>

namespace stuff {

    // Generate size in bytes from size in kb, mb, or gb.
    // For example,
    //     set_buffer(KiB(64));
    inline constexpr size_t KiB(size_t val)
    {
        return val * 1024;
    }

    inline constexpr size_t MiB(size_t val)
    {
        return val * 1024 * 1024;
    }

    inline constexpr size_t GiB(size_t val)
    {
        return val * 1024 * 1024 * 1024;
    }

} // namespace stuff

#endif // STUFF_CORE_UNITS_H
