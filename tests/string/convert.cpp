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
#include <string>
#include <stuff/string/convert.h>

using namespace stuff::string;

TEST_CASE("convert a string to a number", "[string]")
{

    SECTION("an empty string")
    {
        REQUIRE(to_number<int>("", 0) == 0);
        REQUIRE(to_number<int>("", 5) == 5);
        REQUIRE_THROWS(to_number<int>(""));
    }

    SECTION("a bad string")
    {
        // semantics for T to_number(std::string_view view, T missing)
        REQUIRE_THROWS(to_number<int>("12z34", 0));
        REQUIRE_THROWS(to_number<int>("12z34"));
    }

    SECTION("a good number")
    {
        REQUIRE(to_number<int>("1", 0) == 1);
        REQUIRE(to_number<int>("1") == 1);
        REQUIRE(to_number<int>("123456", 0) == 123456);
        REQUIRE(to_number<int>("123456") == 123456);
    }
}
