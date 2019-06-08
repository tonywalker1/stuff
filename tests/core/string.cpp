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

#include <stuff/core/string.h>
#include <stuff/core/random.h>
#include <catch2/catch.hpp>
#include <string>

using namespace stuff;

SCENARIO("splitting a string", "[string]") {
    // setup an array to catch the parts of the string
    std::vector<std::string_view> list;
    auto lambda = [&list](std::string_view line) {
        list.push_back(line);
    };

    GIVEN("an empty string") {
        std::string text = "";
        THEN("should return one empty string") {
            split_string(text, '\n', lambda);
            CHECK(list.size() == 1);
            CHECK(list[0] == "");
        }
    }

    GIVEN("only one separator") {
        std::string text = ",";
        THEN("two empty items should be found") {
            split_string(text, ',', lambda);
            CHECK(list.size() == 2);
            CHECK(list[0] == "");
            CHECK(list[1] == "");
        }
    }

    GIVEN("only two separators") {
        std::string text = ",,";
        THEN("three empty items should be found") {
            split_string(text, ',', lambda);
            CHECK(list.size() == 3);
            CHECK(list[0] == "");
            CHECK(list[1] == "");
            CHECK(list[2] == "");
        }
    }

    GIVEN("only one item and no separators") {
        std::string text = "one";
        THEN("one item should be found") {
            split_string(text, ',', lambda);
            CHECK(list.size() == 1);
            CHECK(list[0] == "one");
        }
    }

    GIVEN("one item and one separator") {
        std::string text = "one,";
        THEN("two items should be found") {
            split_string(text, ',', lambda);
            CHECK(list.size() == 2);
            CHECK(list[0] == "one");
            CHECK(list[1] == "");
        }
    }

    GIVEN("two items and one separator") {
        std::string text = "one,two";
        THEN("two items should be found") {
            split_string(text, ',', lambda);
            CHECK(list.size() == 2);
            CHECK(list[0] == "one");
            CHECK(list[1] == "two");
        }
    }

    GIVEN("two items and two separators") {
        std::string text = "one,two,";
        THEN("three items should be found") {
            split_string(text, ',', lambda);
            CHECK(list.size() == 3);
            CHECK(list[0] == "one");
            CHECK(list[1] == "two");
            CHECK(list[2] == "");
        }
    }

    GIVEN("two items and two separators") {
        std::string text = "one,,two";
        THEN("three items should be found") {
            split_string(text, ',', lambda);
            CHECK(list.size() == 3);
            CHECK(list[0] == "one");
            CHECK(list[1] == "");
            CHECK(list[2] == "two");
        }
    }
}

SCENARIO("converting a string to an int", "[string]") {
    GIVEN("an emptry string") {
        THEN("zero is returned") {
            CHECK(to_int("")    == 0);
            CHECK(to_int("123") == 123);
        }
    }
}

SCENARIO("converting a string to a double", "[string]") {
    GIVEN("unusual/atypical values") {
        THEN("the result is expected") {
            CHECK(to_double("")    == 0.0);
            CHECK(to_double(".0")  == 0.0);
            CHECK(to_double("0.")  == 0.0);
            CHECK(to_double("0.0") == 0.0);

            CHECK(to_double("-.0")  == 0.0);
            CHECK(to_double("-0.")  == 0.0);
            CHECK(to_double("-0.0") == 0.0);

            CHECK(to_double("1.0") == 1.0);
            CHECK(to_double("1.01") == 1.01);
            CHECK(to_double("1.000000001") == 1.000000001);
        }
    }
}
