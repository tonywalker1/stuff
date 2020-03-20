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
#include <stuff/string/split.h>

using namespace stuff::container;
using namespace stuff::string;

TEST_CASE("string_tokenizer", "[string]")
{

    SECTION("tokenizing an empty string")
    {
        string_tokenizer stok {""};

        // check initial conditions
        REQUIRE(stok.head().empty());
        REQUIRE(stok.tail().empty());
        REQUIRE(!stok.is_done());
        REQUIRE_FALSE(!stok);
        REQUIRE(stok);

        // calling next on an empty string should have no effect
        auto head = stok.next();
        REQUIRE(head.empty());
        REQUIRE(stok.head().empty());
        REQUIRE(stok.tail().empty());
        REQUIRE(stok.is_done());
        REQUIRE(!stok);
        REQUIRE_FALSE(stok);
    }

    SECTION("tokenizing one token")
    {
        string_tokenizer stok {"something"};

        // check initial conditions
        REQUIRE(stok.head().empty());
        REQUIRE(stok.tail() == "something");
        REQUIRE(!stok.is_done());

        auto head = stok.next();
        REQUIRE(head == "something");
        REQUIRE(stok.head() == "something");
        REQUIRE(stok.tail().empty());
        REQUIRE(stok.is_done());
    }

    SECTION("tokenizing two tokens")
    {
        string_tokenizer stok {"one two"};

        // check initial conditions
        REQUIRE(stok.head().empty());
        REQUIRE(stok.tail() == "one two");
        REQUIRE(!stok.is_done());

        auto head = stok.next();
        REQUIRE(head == "one");
        REQUIRE(stok.head() == "one");
        REQUIRE(stok.tail() == "two");
        REQUIRE(!stok.is_done());

        head = stok.next();
        REQUIRE(head == "two");
        REQUIRE(stok.head() == "two");
        REQUIRE(stok.tail().empty());
        REQUIRE(stok.is_done());
    }

    SECTION("tokenizing different tokens")
    {
        string_tokenizer stok {"one two,three"};

        // check initial conditions
        REQUIRE(stok.head().empty());
        REQUIRE(stok.tail() == "one two,three");
        REQUIRE(!stok.is_done());

        auto head = stok.next();
        REQUIRE(head == "one");
        REQUIRE(stok.head() == "one");
        REQUIRE(stok.tail() == "two,three");
        REQUIRE(!stok.is_done());

        head = stok.next(',');
        REQUIRE(head == "two");
        REQUIRE(stok.head() == "two");
        REQUIRE(stok.tail() == "three");
        REQUIRE(!stok.is_done());

        head = stok.next();
        REQUIRE(head == "three");
        REQUIRE(stok.head() == "three");
        REQUIRE(stok.tail().empty());
        REQUIRE(stok.is_done());
    }

    SECTION("tokenizing with a terminal separator")
    {
        string_tokenizer stok {"one "};

        // check initial conditions
        REQUIRE(stok.head().empty());
        REQUIRE(stok.tail() == "one ");
        REQUIRE(!stok.is_done());

        auto head = stok.next();
        REQUIRE(head == "one");
        REQUIRE(stok.head() == "one");
        REQUIRE(stok.tail().empty());
        REQUIRE(!stok.is_done());

        head = stok.next();
        REQUIRE(head.empty());
        REQUIRE(stok.head().empty());
        REQUIRE(stok.tail().empty());
        REQUIRE(stok.is_done());
    }

    SECTION("tokenizing with two terminal separators")
    {
        string_tokenizer stok {"one\n\n"};

        // check initial conditions
        REQUIRE(stok.head().empty());
        REQUIRE(stok.tail() == "one\n\n");
        REQUIRE(!stok.is_done());

        auto head = stok.next('\n');
        REQUIRE(head == "one");
        REQUIRE(stok.head() == "one");
        REQUIRE(stok.tail() == "\n");
        REQUIRE(!stok.is_done());

        head = stok.next('\n');
        REQUIRE(head.empty());
        REQUIRE(stok.head().empty());
        REQUIRE(stok.tail().empty());
        REQUIRE(!stok.is_done());

        head = stok.next('\n');
        REQUIRE(head.empty());
        REQUIRE(stok.head().empty());
        REQUIRE(stok.tail().empty());
        REQUIRE(stok.is_done());
    }
}

TEST_CASE("split a string with f()", "[string]")
{
    string_view_array list;
    std::string       text;

    SECTION("tokenizing an empty string")
    {
        text = "";
        split_string(text, ' ',
            [&list](std::string_view line) { list.push_back(line); });
        REQUIRE(list.size() == 1);
        REQUIRE(list[0] == "");
    }

    SECTION("tokenizing one token")
    {
        text = "one";
        split_string(text, ' ',
            [&list](std::string_view line) { list.push_back(line); });
        REQUIRE(list.size() == 1);
        REQUIRE(list[0] == "one");
    }

    SECTION("tokenizing two tokens")
    {
        text = "one two";
        split_string(text, ' ',
            [&list](std::string_view line) { list.push_back(line); });
        REQUIRE(list.size() == 2);
        REQUIRE(list[0] == "one");
        REQUIRE(list[1] == "two");
    }

    SECTION("tokenizing three empty tokens")
    {
        text = ",,";
        split_string(text, ',',
            [&list](std::string_view line) { list.push_back(line); });
        REQUIRE(list.size() == 3);
        REQUIRE(list[0] == "");
        REQUIRE(list[1] == "");
        REQUIRE(list[2] == "");
    }
}

TEST_CASE("split a string into a string_view_array", "[string]")
{
    std::string text;

    SECTION("tokenizing an empty string")
    {
        text      = "";
        auto list = split_string(text, ' ');
        REQUIRE(list.size() == 1);
        REQUIRE(list[0] == "");
    }

    SECTION("tokenizing one token")
    {
        text      = "one";
        auto list = split_string(text, ' ');
        REQUIRE(list.size() == 1);
        REQUIRE(list[0] == "one");
    }

    SECTION("tokenizing two tokens")
    {
        text      = "one two";
        auto list = split_string(text, ' ');
        REQUIRE(list.size() == 2);
        REQUIRE(list[0] == "one");
        REQUIRE(list[1] == "two");
    }

    SECTION("tokenizing three empty tokens")
    {
        text      = ",,";
        auto list = split_string(text, ',');
        REQUIRE(list.size() == 3);
        REQUIRE(list[0] == "");
        REQUIRE(list[1] == "");
        REQUIRE(list[2] == "");
    }
}
