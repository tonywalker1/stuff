// Copyright (C) 2019  Tony Walker
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

SCENARIO("expanding a tilde to the home directory", "[filesystem]") {
    WHEN("the path starts with a tilde") {
        THEN("the tilde should be replaced") {
            CHECK(expand_home("~") == home_dir());
            CHECK(expand_home("~/some/files")
                == home_dir().concat("/some/files"));
        }
    }
    WHEN("the path does not start with a tilde") {
        THEN("the path is unchanged") {
            CHECK(expand_home("/home/user") == "/home/user");
            CHECK(expand_home("/home/user/some/files")
                == "/home/user/some/files");
        }
    }
}
