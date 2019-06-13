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

#include <stuff/core/exception.h>
#include <catch2/catch.hpp>

using namespace stuff;

SCENARIO("defining a new exception type", "[exception]") {
    STUFF_DEFINE_EXCEPTION(stuff, generic_error);
    WHEN("throwing the exception") {
        THEN("it can be caught by its type or base types") {
            CHECK_THROWS_AS(throw stuff {""}, stuff);
            CHECK_THROWS_AS(throw stuff {""}, generic_error);
            CHECK_THROWS_AS(throw stuff {""}, std::runtime_error);
            CHECK_THROWS_AS(throw stuff {""}, std::exception);
        }
        THEN("the message should be returned") {
            CHECK_THROWS_WITH(throw stuff {"the answer is 42"},
                "the answer is 42");
        }
    }
}

SCENARIO("using the throw macro", "[exception]") {
    THEN("the exception should be thrown") {
        CHECK_THROWS_AS(STUFF_THROW(generic_error, "the answer is 42"),
            generic_error);
    }
    THEN("the message should be returned") {
        CHECK_THROWS_WITH(STUFF_THROW(generic_error, "the answer is 42"),
            "generic_error: the answer is 42");
    }
}

SCENARIO("using nested exceptions", "[exception]") {
    STUFF_DEFINE_EXCEPTION(inner, generic_error);
    STUFF_DEFINE_EXCEPTION(outer, generic_error);
    auto f  =[]() {
        try {
            STUFF_THROW(inner, "computation error");
        }
        catch (const std::exception& e) {
            try {
                STUFF_NESTED_THROW(outer, "the answer should have been 42");
            }
            catch (const std::exception& e) {
                throw;
            }
        }
    };

    THEN("the nested messages should be returned") {
        CHECK_THROWS_WITH(f(), "outer: the answer should have been 42");
        try {
            f();
        }
        catch (const std::exception& e) {
            CHECK(to_string(e) ==
                "outer: the answer should have been 42\n"
                "  inner: computation error");
        }
    }
}