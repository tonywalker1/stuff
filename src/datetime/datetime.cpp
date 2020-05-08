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

#include <array>
#include <date/date.h>
#include <stuff/datetime/datetime.h>
#include <stuff/string/convert.h>
#include <stuff/string/split.h>

namespace stuff::datetime {

    namespace detail {

        date::year to_year(std::string_view view)
        {
            return static_cast<date::year>(string::to_number<int>(view));
        }

        [[nodiscard]] date::month to_month(std::string_view view)
        {
            return static_cast<date::month>(string::to_number<unsigned>(view));
        }

        [[nodiscard]] date::day to_day(std::string_view view)
        {
            return static_cast<date::day>(string::to_number<int>(view));
        }

        duration to_hours(std::string_view view)
        {
            return std::chrono::hours(string::to_number<long>(view));
        }

        duration to_minutes(std::string_view view)
        {
            return std::chrono::minutes(string::to_number<long>(view));
        }

        duration to_seconds(std::string_view view)
        {
            return std::chrono::seconds(string::to_number<long>(view));
        }

        duration to_nanoseconds(std::string_view view)
        {
            // Ideally, the string of digits to convert to nanoseconds will be
            // nine digits in length. However, some data sources will omit
            // trailing zeros. A quick way to handle zero to nine digits is via
            // a lookup table where the input-string length yields the precision
            // (well, actually the inverse of the precision) of the input
            // string.
            static std::array<long, 10> prec {0, 100000000, 10000000, 1000000,
                100000, 10000, 1000, 100, 10, 1};

            STUFF_EXPECTS(view.size() < 10, datetime_error,
                "nanoseconds will overflow in \"{}\"", view);
            return std::chrono::nanoseconds(
                string::to_number<long>(view, 0) * prec[view.size()]);
        }

    } // namespace detail

    // {year}-{month}-{day}T{hour}:{minute}:{second}.{nanoseconds}{zone}
    const char* sys_fmt_str {"{}-{:02d}-{:02d}T{:02d}:{:02d}:{:02d}.{:09d}Z"};
    const char* local_fmt_str {"{}-{:02d}-{:02d}T{:02d}:{:02d}:{:02d}.{:09d}"};
    const char* zoned_fmt_str {
        "{}-{:02d}-{:02d}T{:02d}:{:02d}:{:02d}.{:09d} {}"};

    time_zone nyc_tz() noexcept
    {
        static const auto tz = date::locate_zone("America/New_York");
        return tz;
    }

    sys_time current_time() noexcept { return clock::now(); }

    zoned_time current_time(time_zone tz)
    {
        return date::make_zoned(tz, clock::now());
    }

    sys_time find_sunday(sys_time t)
    {
        return find_sunday(date::floor<date::days>(t));
    }

    zoned_time find_sunday(zoned_time t)
    {
        return date::make_zoned(t.get_time_zone(),
            find_sunday(date::floor<date::days>(t.get_local_time())));
    }

    sys_time to_sys_time(std::string_view view)
    {
        try {
            sys_time                 result;
            string::string_tokenizer tok {view};

            // parse year, month, and day
            result = date::sys_days(date::year_month_day {
                detail::to_year(tok.next('-')), detail::to_month(tok.next('-')),
                detail::to_day(tok.next("T "))});

            // parse hours, minutes, seconds, and nanoseconds
            result += detail::to_hours(tok.next(':'));
            result += detail::to_minutes(tok.next(':'));
            result += detail::to_seconds(tok.next(".Z"));
            result += detail::to_nanoseconds(tok.next('Z'));

            return result;
        }
        catch (const std::exception& e) {
            STUFF_NESTED_THROW(datetime_error, "invalid date string: {}", view);
        }
    }

    local_time to_local_time(std::string_view view)
    {
        try {
            local_time               result;
            string::string_tokenizer tok {view};

            // parse year, month, and day
            result = date::local_days(date::year_month_day {
                detail::to_year(tok.next('-')), detail::to_month(tok.next('-')),
                detail::to_day(tok.next("T "))});

            // parse hours, minutes, seconds, and nanoseconds
            result += detail::to_hours(tok.next(':'));
            result += detail::to_minutes(tok.next(':'));
            result += detail::to_seconds(tok.next("."));
            result += detail::to_nanoseconds(tok.tail());

            return result;
        }
        catch (const std::exception& e) {
            STUFF_NESTED_THROW(datetime_error, "invalid date string: {}", view);
        }
    }

    sys_time to_sys_time(std::string_view local_view, time_zone local_tz)
    {
        zoned_time zt = date::make_zoned(local_tz, to_local_time(local_view));
        return zt.get_sys_time();
    }

    std::string to_string(sys_time t)
    {
        // break into ymd and time-of-day
        auto dp  = date::floor<date::days>(t);
        auto ymd = date::year_month_day(dp);
        auto tod = date::make_time(t - dp);

        // format the string
        return fmt::format(sys_fmt_str, static_cast<int>(ymd.year()),
            static_cast<unsigned>(ymd.month()),
            static_cast<unsigned>(ymd.day()), tod.hours().count(),
            tod.minutes().count(), tod.seconds().count(),
            tod.subseconds().count());
    }

    std::string to_string(local_time t)
    {
        // break into ymd and time-of-day
        auto dp  = date::floor<date::days>(t);
        auto ymd = date::year_month_day(dp);
        auto tod = date::make_time(t - dp);

        // format the string
        return fmt::format(local_fmt_str, static_cast<int>(ymd.year()),
            static_cast<unsigned>(ymd.month()),
            static_cast<unsigned>(ymd.day()), tod.hours().count(),
            tod.minutes().count(), tod.seconds().count(),
            tod.subseconds().count());
    }

    std::string to_string(zoned_time t)
    {
        // break into ymd and time-of-day
        auto dp  = date::floor<date::days>(t.get_local_time());
        auto ymd = date::year_month_day(dp);
        auto tod = date::make_time(t.get_local_time() - dp);

        // format the string
        return fmt::format(zoned_fmt_str, static_cast<int>(ymd.year()),
            static_cast<unsigned>(ymd.month()),
            static_cast<unsigned>(ymd.day()), tod.hours().count(),
            tod.minutes().count(), tod.seconds().count(),
            tod.subseconds().count(), t.get_time_zone()->name());
    }

} // namespace stuff::datetime
