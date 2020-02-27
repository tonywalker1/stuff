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

#include <catch2/catch.hpp>
#include <stuff/algorithm/random.h>
#include <thread>

using namespace stuff::algorithm;


TEST_CASE("random number object creation", "[random]")
{
    SECTION("bad ranges should fail")
    {
        REQUIRE_THROWS_AS(random_integer<int>(10, -10), random_error);
        REQUIRE_THROWS_AS(random_real<double>(10, -10), random_error);
    }

    SECTION("Two generators should not generate the same values.")
    {
        REQUIRE(
            random_integer<int>(-10, 10)() != random_integer<int>(-10, 10)());
    }
}
