//
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
//

#include <catch2/catch.hpp>
#include <stuff/core/units.h>

using namespace stuff::core;

TEST_CASE("memory conversions", "[units]")
{

    REQUIRE(KiB(4) == 4096);
    REQUIRE(MiB(4) == 4194304);
    REQUIRE(GiB(4) == 4294967296);

    // Just make sure they are constexpr (no typo's)
    static_assert(KiB(4) == 4 * 1024);
    static_assert(MiB(4) == 4 * 1024 * 1024);
    static_assert(GiB(4) == 4lu * 1024lu * 1024lu * 1024lu);
}
