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

#ifndef STUFF_CORE_STRING_H
#define STUFF_CORE_STRING_H

#include <stuff/core/exception.h>
#include <string>
#include <vector>

namespace stuff::core {

    STUFF_DEFINE_EXCEPTION(string_conversion_error, generic_error);

    using string_array = std::vector<std::string>;

    //
    // Tokenize a string based on sep.
    //
    template <typename T>
    void split_string(std::string_view view, char sep, T callback)
    {
        size_t pos = 0;
        do {
            pos = view.find(sep);
            callback(view.substr(0, pos));
            view.remove_prefix(pos + 1);
        } while (pos != view.npos);
    }

    //
    // Fast conversion of strings to integers or doubles (opposite of to_string).
    //
    // The standard conversion routines are slower than they could be because
    // they use locales, parse special characters, etc. These functions parse
    // only ASCII numbers and make no other provisions.
    //
    // Note:
    // - I chose to convert the empty string to the value zero. This enables
    //   significant advantages when parsing, for example, CSV files with empty
    //   fields: "1,,2". See the unit tests for examples.
    //
    int    to_int(std::string_view view);
    double to_double(std::string_view view);

} // namespace stuff::core

#endif // STUFF_CORE_STRING_H
