//
// Copyright (C) 2019-2020  Tony Walker
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

#include <boost/convert.hpp>
#include <boost/convert/spirit.hpp>
#include <string>
#include <string_view>
#include <stuff/core/exception.h>

#ifndef STUFF_STRING_CONVERT_H
    #define STUFF_STRING_CONVERT_H

namespace stuff::string {

    STUFF_DEFINE_EXCEPTION(string_conversion_error, core::generic_error);

    //
    // Fast conversion of a string to a number.
    //
    // An empty string will not be treated as an error, instead the value given
    // by "missing" will be returned. Using zero, for example, can be
    // really useful when parsing a CSV file with empty columns.
    //
    // This function will throw on error.
    //
    // Years ago, I wrote code that beat the standard C/C++ library functions
    // substantially. As I started to migrate that code into this library, I
    // noticed that the standard library had improved substantially. Also, some
    // of the boost::convert converters were on par with my code. Because it is
    // always better to use code from better programmers, I switched to
    // boost::convert. There are a couple of lessons here, but one is that
    // C++ and Boost are always evolving. Periodically, I will benchmark some
    // of the best code and reserve the right to change the underlying
    // implementation!
    //
    // See stuff/benchmarks/core/stuff_core_benchmarks to obtain performance
    // numbers for your system.
    //
    // Parameters:
    //   T        Type of the number (e.g., int).
    //   view     String to convert to a number of type T.
    //   missing  Value to return if view is empty.
    //
    // Returns:
    //   Number of type T.
    //
    template <typename T>
    [[nodiscard]] inline T to_number(std::string_view view, T missing)
    {
        if (view.empty()) {
            return missing;
        }
        boost::cnv::spirit cnv;
        auto               result = boost::convert<T>(view, cnv);
        STUFF_EXPECTS(result, string_conversion_error,
            "can not convert \"{}\" to an integer", view);
        return result.value();
    }

    //
    // Same as above, but an empty string is considered an error.
    //
    template <typename T>
    [[nodiscard]] inline T to_number(std::string_view view)
    {
        boost::cnv::spirit cnv;
        auto               result = boost::convert<T>(view, cnv);
        STUFF_EXPECTS(result, string_conversion_error,
            "can not convert \"{}\" to an integer", view);
        return result.value();
    }

} // namespace stuff::string

#endif // STUFF_STRING_CONVERT_H
