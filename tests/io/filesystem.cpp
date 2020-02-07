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

#include <stuff/io/filesystem.h>
#include <catch2/catch.hpp>

using namespace stuff::io;

TEST_CASE("strings can be converted to paths", "[filesystem]")
{
    const fs::path empty;
    const fs::path home {home_dir()};

    SECTION("the string is the nullptr or an empty string") {
        REQUIRE(expand_home(nullptr)             == empty);
        REQUIRE(expand_home("")                  == empty);
        REQUIRE(expand_home(std::string_view {}) == empty);
        REQUIRE(expand_home(std::string {})      == empty);
    }
    SECTION("the string is ~ or starts with ~/") {
        REQUIRE(expand_home("~")       == home);
        REQUIRE(expand_home("~/")      == home.native() + "/");
        REQUIRE(expand_home("~/stuff") == home.native() + "/stuff");
    }
    SECTION("otherwise, any string ~ or not is left unchanged") {
        REQUIRE(expand_home("/")          == "/");
        REQUIRE(expand_home(".")          == ".");
        REQUIRE(expand_home("a")          == "a");
        REQUIRE(expand_home("~stuff")     == "~stuff");
        REQUIRE(expand_home("stuff~")     == "stuff~");
        REQUIRE(expand_home("/some/path") == "/some/path");
    }
}
