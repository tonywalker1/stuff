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

#include <stuff/include/stuff/core/string.h> // NOLINT(modernize-deprecated-headers,hicpp-deprecated-headers)
#include <catch2/catch.hpp>
#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>
#include <boost/convert/strtol.hpp>
#include <boost/convert/spirit.hpp>
#include <string>

using namespace stuff::core;

TEST_CASE("convert strings to integers", "[string_benchmarks]") {

    std::string str {"1234567890"};

    BENCHMARK("lexical_cast") {
        return boost::lexical_cast<long>(str);
    };

    BENCHMARK("stol") {
        return std::stol(str);
    };

    BENCHMARK("boost::convert w/ lexical_cast") {
        boost::cnv::lexical_cast cnv;
        return boost::convert<long>(str, cnv).value();
    };

    BENCHMARK("boost::convert w/ strtol") {
        boost::cnv::strtol cnv;
        return boost::convert<long>(str, cnv).value();
    };

    BENCHMARK("boost::convert w/ spirit") {
        boost::cnv::spirit cnv;
        return boost::convert<long>(str, cnv).value();
    };

    BENCHMARK("stuff::core::to_number") {
        return stuff::core::to_number<long>(str).value();
    };

    BENCHMARK("stuff::core::to_number w/ missing") {
        return stuff::core::to_number<long>(str, 0);
    };

}

TEST_CASE("convert strings to doubles", "[string_benchmarks]") {

    std::string str {"1.2345678901"};

    BENCHMARK("lexical_cast") {
        return boost::lexical_cast<double>(str);
    };

    BENCHMARK("stod") {
        return std::stod(str);
    };

    BENCHMARK("boost::convert w/ lexical_cast") {
        boost::cnv::lexical_cast cnv;
        return boost::convert<double>(str, cnv).value();
    };

    BENCHMARK("boost::convert w/ strtol") {
        boost::cnv::strtol cnv;
        return boost::convert<double>(str, cnv).value();
    };

    BENCHMARK("boost::convert w/ spirit") {
        boost::cnv::spirit cnv;
        return boost::convert<double>(str, cnv).value();
    };

    BENCHMARK("stuff::core::to_number") {
        return stuff::core::to_number<double>(str).value();
    };

    BENCHMARK("stuff::core::to_number w/ missing") {
        return stuff::core::to_number<double>(str, 0);
    };

}
