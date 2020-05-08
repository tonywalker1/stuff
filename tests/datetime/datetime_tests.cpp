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
#include <sstream>
#include <stuff/datetime/datetime.h>

using namespace stuff::datetime;

sys_time parse_sys_date(std::string view)
{
    sys_time          tp;
    std::stringstream ss {view};
    ss >> date::parse("%FT%T", tp);
    return tp;
}

local_time parse_local_date(std::string view)
{
    local_time        tp;
    std::stringstream ss {view};
    ss >> date::parse("%FT%T", tp);
    return tp;
}


TEST_CASE("conversion helpers", "[datetime]")
{
    REQUIRE(detail::to_year("2020") == date::year {2020});
    REQUIRE(detail::to_month("03") == date::month {3});
    REQUIRE(detail::to_day("14") == date::day {14});

    REQUIRE(detail::to_hours("15") == std::chrono::hours {15});
    REQUIRE(detail::to_minutes("09") == std::chrono::minutes {9});
    REQUIRE(detail::to_seconds("26") == std::chrono::seconds {26});

    REQUIRE(detail::to_nanoseconds("") == std::chrono::nanoseconds {});
    REQUIRE(
        detail::to_nanoseconds("1") == std::chrono::nanoseconds {100000000});
    REQUIRE(
        detail::to_nanoseconds("12") == std::chrono::nanoseconds {120000000});
    REQUIRE(
        detail::to_nanoseconds("123") == std::chrono::nanoseconds {123000000});
    REQUIRE(
        detail::to_nanoseconds("1234") == std::chrono::nanoseconds {123400000});
    REQUIRE(detail::to_nanoseconds("12345")
            == std::chrono::nanoseconds {123450000});
    REQUIRE(detail::to_nanoseconds("123456")
            == std::chrono::nanoseconds {123456000});
    REQUIRE(detail::to_nanoseconds("1234567")
            == std::chrono::nanoseconds {123456700});
    REQUIRE(detail::to_nanoseconds("12345678")
            == std::chrono::nanoseconds {123456780});
    REQUIRE(detail::to_nanoseconds("123456789")
            == std::chrono::nanoseconds {123456789});

    REQUIRE_THROWS(detail::to_nanoseconds("1234567890"));
    REQUIRE_THROWS(detail::to_nanoseconds("123456789Z"));
}

TEST_CASE("Convert a string to sys_time", "[datetime]")
{
    // Test the well-formed strings:
    REQUIRE(to_sys_time("2015-03-14T15:09:26.535897932Z")
            == parse_sys_date("2015-03-14T15:09:26.535897932Z"));
    REQUIRE(to_sys_time("2015-03-14 15:09:26.535897932Z")
            == parse_sys_date("2015-03-14T15:09:26.535897932Z"));

    // Test second-precision strings
    REQUIRE(to_sys_time("2015-03-14T15:09:26Z")
            == parse_sys_date("2015-03-14T15:09:26"));
    REQUIRE(to_sys_time("2015-03-14 15:09:26Z")
            == parse_sys_date("2015-03-14T15:09:26Z"));

    // Well-formed string may not have all nine digits (zeros omitted)
    REQUIRE(to_sys_time("2015-03-14T15:09:26.5Z")
            == parse_sys_date("2015-03-14T15:09:26.5"));

    // It's possible the terminal Z is missing (I would prefer not, but is OK)
    REQUIRE(to_sys_time("2015-03-14T15:09:26.535897932")
            == parse_sys_date("2015-03-14T15:09:26.535897932"));
    REQUIRE(to_sys_time("2015-03-14T15:09:26")
            == parse_sys_date("2015-03-14T15:09:26"));

    // An ill-formed, but OK string...
    REQUIRE(to_sys_time("2015-03-14T15:09:26.")
            == parse_sys_date("2015-03-14T15:09:26"));

    // Check error path
    REQUIRE_THROWS(to_sys_time("201q-03-14T15:09:26.535897932Z"));
    REQUIRE_THROWS(to_sys_time("201q-03-14T15:09:26.5358979321q"));
}

TEST_CASE("Convert a string to local_time", "[datetime]")
{
    // Test the well-formed strings:
    REQUIRE(to_local_time("2015-03-14T15:09:26.535897932")
            == parse_local_date("2015-03-14T15:09:26.535897932"));
    REQUIRE(to_local_time("2015-03-14 15:09:26.535897932")
            == parse_local_date("2015-03-14T15:09:26.535897932"));

    //    // Test second-precision strings
    REQUIRE(to_local_time("2015-03-14T15:09:26")
            == parse_local_date("2015-03-14T15:09:26"));
    REQUIRE(to_local_time("2015-03-14 15:09:26")
            == parse_local_date("2015-03-14T15:09:26"));

    // Well-formed string may not have all nine digits (zeros omitted)
    REQUIRE(to_local_time("2015-03-14T15:09:26.5")
            == parse_local_date("2015-03-14T15:09:26.5"));

    // An ill-formed, but OK string...
    REQUIRE(to_local_time("2015-03-14T15:09:26.")
            == parse_local_date("2015-03-14T15:09:26"));

    // Check error path
    REQUIRE_THROWS(to_local_time("201q-03-14T15:09:26.535897932Z"));
    REQUIRE_THROWS(to_local_time("201q-03-14T15:09:26.5358979321q"));
}


TEST_CASE("Convert a time to a string", "[datetime]")
{
    // for a sys_time
    REQUIRE(to_string(to_sys_time("2015-03-14T15:09:26.535897932Z"))
            == "2015-03-14T15:09:26.535897932Z");
    REQUIRE(to_string(to_sys_time("2015-03-14T15:09:26.535Z"))
            == "2015-03-14T15:09:26.535000000Z");
    REQUIRE(to_string(to_sys_time("2015-03-04T05:09:06Z"))
            == "2015-03-04T05:09:06.000000000Z");

    // for a local_time
    REQUIRE(to_string(to_local_time("2015-03-14T15:09:26.535897932"))
            == "2015-03-14T15:09:26.535897932");
    REQUIRE(to_string(to_local_time("2015-03-14T15:09:26.535"))
            == "2015-03-14T15:09:26.535000000");
    REQUIRE(to_string(to_local_time("2015-03-04T05:09:06"))
            == "2015-03-04T05:09:06.000000000");

    // for a zoned time
    REQUIRE(to_string(date::make_zoned(
                nyc_tz(), to_local_time("2015-03-14T15:09:26.535897932")))
            == "2015-03-14T15:09:26.535897932 America/New_York");
}
