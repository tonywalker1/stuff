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
#include <date/date.h>
#include <stuff/datetime/datetime.h>
#include <stuff/string/split.h>

using namespace stuff::container;
using namespace stuff::datetime;
using namespace stuff::string;

TEST_CASE("convert a date to a string", "[datetime_benchmarks]")
{
    auto now {current_time()};

    BENCHMARK("date::format") { return date::format("%FT%TZ", now); };

    BENCHMARK("stuff::datetime::to_string") { return to_string(now); };
}

TEST_CASE("convert a date string to a date", "[datetime_benchmarks]")
{
    std::string datestr {"2015-03-14T15:09:26.535897932Z\n"};

    BENCHMARK("stringstream overhead") { std::stringstream ss {datestr}; };

    BENCHMARK("date::parse")
    {
        std::stringstream ss {datestr};
        sys_time          t;
        ss >> date::parse("%FT%TZ", t);
        return t;
    };

    BENCHMARK("tokenizer overhead") { string_tokenizer stok {datestr}; };

    BENCHMARK("stuff::to_sys_time")
    {
        string_tokenizer stok {datestr};
        return to_sys_time(stok.next('\n'));
    };
}
