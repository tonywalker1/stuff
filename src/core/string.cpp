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

#include <stuff/core/string.h>
#include <stuff/core/exception.h>
#include <charconv>

namespace stuff::core {

    int to_int(std::string_view view)
    {
        if (view.empty()) {
            return 0;
        }
        else {
            int tmp;
            auto result = std::from_chars(view.begin(), view.end(), tmp);
            STUFF_EXPECTS(result.ec == std::errc(),
                string_conversion_error,
                "can\'t extract an int from \"{}\"", view);
            return tmp;
        }
    }

    double to_double(std::string_view view)
    {
        // At the moment, from_chars only works for ints; until then, use stod.
        if (view.empty()) {
            return 0;
        }
        else {
            try {
                return std::stod(std::string(view.begin(), view.end()));
            }
            catch (std::exception& e) {
                STUFF_NESTED_THROW(string_conversion_error,
                    "can\'t extract a double from \"{}\"", view);
            }
        }
    }

} // namespace stuff::core
