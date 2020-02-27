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

#include <boost/optional/optional_io.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <stuff/core/string.h>

using namespace stuff::core;

TEST_CASE("string_tokenizer", "[string]")
{

    SECTION("tokenizing an empty string")
    {
        string_tokenizer stok {""};

        // check initial conditions
        REQUIRE(stok.head().empty());
        REQUIRE(stok.tail().empty());
        REQUIRE(!stok.is_done());

        // calling next on an empty string should have no effect
        auto head = stok.next();
        REQUIRE(head.empty());
        REQUIRE(stok.head().empty());
        REQUIRE(stok.tail().empty());
        REQUIRE(stok.is_done());
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
    auto lambda = [&list](std::string_view line) { list.push_back(line); };

    SECTION("tokenizing an empty string")
    {
        std::string text = "";
        split_string(text, ' ', lambda);
        REQUIRE(list.size() == 1);
        REQUIRE(list[0] == "");
    }

    SECTION("tokenizing one token")
    {
        std::string text = "one";
        split_string(text, ' ', lambda);
        REQUIRE(list.size() == 1);
        REQUIRE(list[0] == "one");
    }

    SECTION("tokenizing two tokens")
    {
        std::string text = "one two";
        split_string(text, ' ', lambda);
        REQUIRE(list.size() == 2);
        REQUIRE(list[0] == "one");
        REQUIRE(list[1] == "two");
    }

    SECTION("tokenizing three empty tokens")
    {
        std::string text = ",,";
        split_string(text, ',', lambda);
        REQUIRE(list.size() == 3);
        REQUIRE(list[0] == "");
        REQUIRE(list[1] == "");
        REQUIRE(list[2] == "");
    }
}

TEST_CASE("split a string into a string_view_array", "[string]")
{
    SECTION("tokenizing an empty string")
    {
        std::string text = "";
        auto        list = split_string(text, ' ');
        REQUIRE(list.size() == 1);
        REQUIRE(list[0] == "");
    }

    SECTION("tokenizing one token")
    {
        std::string text = "one";
        auto        list = split_string(text, ' ');
        REQUIRE(list.size() == 1);
        REQUIRE(list[0] == "one");
    }

    SECTION("tokenizing two tokens")
    {
        std::string text = "one two";
        auto        list = split_string(text, ' ');
        REQUIRE(list.size() == 2);
        REQUIRE(list[0] == "one");
        REQUIRE(list[1] == "two");
    }

    SECTION("tokenizing three empty tokens")
    {
        std::string text = ",,";
        auto        list = split_string(text, ',');
        REQUIRE(list.size() == 3);
        REQUIRE(list[0] == "");
        REQUIRE(list[1] == "");
        REQUIRE(list[2] == "");
    }
}

TEST_CASE("convert a string to a number", "[string]")
{

    SECTION("an empty string")
    {
        // semantics for boost::optional<T> to_number(std::string_view view)
        REQUIRE_THROWS(to_number<int>("").value());
        // semantics for T to_number(std::string_view view, T missing)
        REQUIRE(to_number<int>("", 0) == 0);
        REQUIRE(to_number<int>("", 5) == 5);
    }

    SECTION("a bad string")
    {
        // semantics for boost::optional<T> to_number(std::string_view view)
        REQUIRE_THROWS(to_number<int>("12z34").value());
        // semantics for T to_number(std::string_view view, T missing)
        REQUIRE_THROWS(to_number<int>("12z34", 0));
    }

    SECTION("a good number")
    {
        REQUIRE(to_number<int>("1").value() == 1);
        REQUIRE(to_number<int>("1", 0) == 1);

        REQUIRE(to_number<int>("123456").value() == 123456);
        REQUIRE(to_number<int>("123456", 0) == 123456);
    }
}